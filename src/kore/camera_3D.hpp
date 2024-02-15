#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "ICamera.hpp"

enum Camera3D_Movement  {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float FOV         =  45.0f;
const glm::vec3 UP      =  glm::vec3(0.0f, 1.0f, 0.0f);

class Camera3D : public ICamera {
    public:
        Camera3D(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float win_width = 800, float win_height = 600, bool is_fps = false) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(UP), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV), Pitch(PITCH), Yaw(YAW)
        {
            Position = position;
            width = win_width;
            height = win_height;
            fps = is_fps;
            update_camera_vectors();
        }

        glm::mat4 get_view_matrix() const
        {
            return glm::lookAt(Position, Position + Front, Up);
        }

        glm::mat4 get_projection_matrix() const
        {
            return glm::perspective(glm::radians(Fov), width / height, 0.1f, 100.0f);
        }

        void process_keyboard(Camera3D_Movement direction, float deltaTime)
        {
            float velocity = MovementSpeed * deltaTime;
            if (direction == FORWARD)
                Position += Front * velocity;
            if (direction == BACKWARD)
                Position -= Front * velocity;
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;
            if (fps)
                Position.y = 0;
        }

        void process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;

            Yaw   += xoffset;
            Pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch)
            {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }

            // update Front, Right and Up Vectors using the updated Euler angles
            update_camera_vectors();
        }

        void process_mouse_scroll(float yoffset)
        {
            Fov -= (float)yoffset;
            if (Fov < 1.0f)
                Fov = 1.0f;
            if (Fov > 45.0f)
                Fov = 45.0f;
        }

    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        
        float Yaw;
        float Pitch;
        
        float MovementSpeed;
        float MouseSensitivity;
        float Fov;

        float width;
        float height;

        bool fps;

    private:
        void update_camera_vectors()
        {
            // calculate the new Front vector
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, Front));
        }
};