#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ICamera {
    public:
        ICamera(){} 
        virtual ~ICamera(){}
        virtual glm::mat4 get_view_matrix() const = 0;
        virtual glm::mat4 get_projection_matrix() const = 0;
    public:
        // glm::vec3 Position;
        // glm::vec3 Front;
        // glm::vec3 Up;
        // glm::vec3 Right;
        // glm::vec3 WorldUp;
};