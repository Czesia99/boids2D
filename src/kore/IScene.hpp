#pragma once

#include <glad/glad.h>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IScene {
    public:
        virtual ~IScene(){}
        virtual void update() = 0;
        virtual void scene_clear() = 0;
        virtual void process_input() = 0;
        virtual void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) = 0;
        virtual void left_click_callback(GLFWwindow* window, int button, int action, int mods) = 0;
        virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) = 0;
        virtual void framebuffer_size_callback(GLFWwindow* window, int width, int height) = 0;
};