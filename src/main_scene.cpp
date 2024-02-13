#include "main_scene.hpp"
#include "boid.hpp"


float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

MainScene::MainScene(Context &ctx) : ctx(ctx)
{
    glEnable(GL_DEPTH_TEST);
    //glfwSetInputMode(ctx.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    boidShader = Shader("shader.vs", "shader.fs");
    camera = CameraOrtho(glm::vec3(0.0f, 0.0f, 0.0f), ctx.win_width, ctx.win_height, true);
    //manager = std::make_unique<BoidManager>(ctx, 30);
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

    // if (glfwGetKey(ctx.window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.process_keyboard(FORWARD, deltaTime);
    // if (glfwGetKey(ctx.window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.process_keyboard(BACKWARD, deltaTime);
    // if (glfwGetKey(ctx.window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.process_keyboard(LEFT, deltaTime);
    // if (glfwGetKey(ctx.window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.process_keyboard(RIGHT, deltaTime);
}

void MainScene::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) 
{
    // float xpos = static_cast<float>(xposIn);
    // float ypos = static_cast<float>(yposIn);

    // if (firstMouse)
    // {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }

    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    // lastX = xpos;
    // lastY = ypos;

    //camera.process_mouse_movement(xoffset, yoffset);
}

void MainScene::left_click_callback(GLFWwindow* window, int button, int action, int mods)
{
        // double xpos, ypos;
        // glfwGetCursorPos(window, &xpos, &ypos);

        // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //     std::cout<< "first if !" << std::endl;
        //     if(start_btn.isClicked(xpos, ypos)) {
        //         std::cout<< "button clicked !" << std::endl;
        //     }
        // }

        // std::cout << "action = " << action << std::endl;
        // std::cout << "button = " << button << std::endl;
        // std::cout << "mods = " << mods << std::endl;
        // std::cout << "xpos = " << xpos << std::endl;
        // std::cout << "ypos = " << ypos << std::endl;
}

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