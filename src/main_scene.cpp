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
    srand (time(NULL));
    int randomx = rand() % static_cast<int>(ctx.win_width) + 0;
    int randomy = rand() % static_cast<int>(ctx.win_width) + 0;
    std::cout << randomx << std::endl;
    boid.transform.position.x = static_cast<float>(randomx);
    boid.transform.position.y = static_cast<float>(randomy);
    boid.transform.scale += 20;
}

void MainScene::update()
{ 
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    boidShader.use();
    boidShader.set_float("time", currentTime);

    boid.transform.position.x += boid.velocity;

    if (boid.transform.position.x >= ctx.win_width)
    {
        boid.transform.position.x = 0;
        
    }
    if (boid.transform.position.y >= ctx.win_height)
    {
        boid.transform.position.y = 0;
    }

    boid.render(boidShader, camera);
}

void MainScene::scene_clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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