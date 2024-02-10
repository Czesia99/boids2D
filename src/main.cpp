#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "kore/context.hpp"
#include "main_scene.hpp"

int main()
{
    Context ctx(800.0f, 600.0f, "Boids2D");

    MainScene scene(ctx);
    IScene *current_scene = &scene;

    ctx.set_callbacks(current_scene);

    while (!glfwWindowShouldClose(ctx.window))
    {

        current_scene->scene_clear();
        current_scene->process_input();
        current_scene->update();

        glfwSwapBuffers(ctx.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}