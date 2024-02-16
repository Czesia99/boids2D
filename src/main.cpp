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
    IScene *current_scene = &scene;

    ctx.set_callbacks(current_scene);

    //SETUP IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(ctx.window, true);
    // ImGui_ImplOpenGL3_Init();

    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();

    while (!glfwWindowShouldClose(ctx.window))
    {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello, world!");
        ImGui::Text("This is some useful text.");
        
        ImGui::Render();
        current_scene->scene_clear();
        current_scene->process_input();
        current_scene->update();
    

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(ctx.window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}