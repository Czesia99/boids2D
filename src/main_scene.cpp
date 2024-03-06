#include "main_scene.hpp"
#include "boid.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

MainScene::MainScene(Context &ctx) : ctx(ctx)
{
    glEnable(GL_DEPTH_TEST);
    //glfwSetInputMode(ctx.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    boidShader = Shader("shader.vs", "shader.fs");
    camera = CameraOrtho(glm::vec3(0.0f, 0.0f, 0.0f), ctx.win_width, ctx.win_height, true);
    manager = new BoidManager(ctx, 300);
}

void MainScene::update()
{

    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    boidShader.use();
    boidShader.set_float("time", currentTime);

    manager->update();
    manager->render(boidShader, camera);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    ImGui::SliderFloat("Speed", &manager->fspeed, 0.0f, 30.0f);
    ImGui::SliderFloat("Separation", &manager->fseparation, 0.0f, 1.0f);
    ImGui::SliderFloat("Alignment", &manager->falignment, 0.0f, 1.0f);
    ImGui::SliderFloat("Cohesion", &manager->fcohesion, 0.0f, 0.03f);
    if (ImGui::Button("reset"))
        manager->default_fvalues();
    if (ImGui::SliderInt("Boids number", &manager->nb_boids, 0, 500))
        manager->resize_boids_number();
    ImGui::Checkbox("Follow Cursor", &manager->mouse_leader);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainScene::scene_clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainScene::process_input()
{
    if (glfwGetKey(ctx.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(ctx.window, true);
}

void MainScene::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {}

void MainScene::left_click_callback(GLFWwindow* window, int button, int action, int mods) {}

void MainScene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) 
{
    camera.process_mouse_scroll(static_cast<float>(yoffset));
}

void MainScene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera.width = width;
    camera.height = height;
    ctx.win_width = width;
    ctx.win_height = height;
}