#pragma once

#include "kore/shader.h"
#include "kore/shape.hpp"
#include "kore/camera_ortho.hpp"
#include "kore/IScene.hpp"
#include "kore/context.hpp"
#include "boid.hpp"

class MainScene : public IScene {
    public:
        MainScene(Context &ctx);
        void update() override;
        void scene_clear() override;
        void process_input() override;
        void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) override;
        void left_click_callback(GLFWwindow* window, int button, int action, int mods) override;
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) override;
        void framebuffer_size_callback(GLFWwindow* window, int width, int height) override;

    public:
        Context &ctx;

    private:
        Shader boidShader;
        BoidManager *manager = nullptr;
        CameraOrtho camera;

        float lastX = ctx.win_width / 2.0f;
        float lastY = ctx.win_height / 2.0f;
        bool firstMouse = true;
        glm::vec3 lightPos;
};