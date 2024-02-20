#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "kore/context.hpp"
#include "main_scene.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main()
{
    Context ctx(1920.0f, 1080.0f, "Boids2D");
    glfwSwapInterval(1); //vsync

    MainScene scene(ctx);
    ctx.current_scene = &scene;

    ctx.run();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}