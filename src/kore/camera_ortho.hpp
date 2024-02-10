#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "ICamera.hpp"

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float FOV         =  45.0f;
const glm::vec3 UP      =  glm::vec3(0.0f, 1.0f, 0.0f);

class CameraOrtho : public ICamera {
    public:
        CameraOrtho(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float win_width = 800, float win_height = 600, bool is_fps = false) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(UP), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV), Pitch(PITCH), Yaw(YAW)
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
            return glm::ortho(0.f, width, 0.f, height, -1.f, 1.f);
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