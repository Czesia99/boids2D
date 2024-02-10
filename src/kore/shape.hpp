#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "transform.hpp"
#include "ICamera.hpp"

//2D PRIMITIVES
class Triangle {
    public:
        Triangle() {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, triangle_vertices.size() * sizeof(float), triangle_vertices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        void render(Shader shader, const ICamera &camera) 
        {
            shader.use();
            glm::mat4 mat = transform.get_model_matrix();
            glm::mat4 projection = camera.get_projection_matrix();
            glm::mat4 view = camera.get_view_matrix();

            shader.set_mat4("model", mat);
            shader.set_mat4("projection", projection);
            shader.set_mat4("view", view);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

    public:
        Transform transform;

    private:
        unsigned int VAO;
        unsigned int VBO;
        //triangle
        std::vector<float> triangle_vertices = {
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        };
};

class Rectangle {
    public:
        Rectangle() {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glGenBuffers(1, &EBO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, rectangle_vertices.size() * sizeof(float), rectangle_vertices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            // glEnableVertexAttribArray(1);
        }

        void render(Shader shader, const ICamera &camera) 
        {
            shader.use();
            glm::mat4 mat = transform.get_model_matrix();
            glm::mat4 projection = camera.get_projection_matrix();
            glm::mat4 view = camera.get_view_matrix();

            shader.set_mat4("model", mat);
            shader.set_mat4("projection", projection);
            shader.set_mat4("view", view);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

    public:
        Transform transform;

    private:
        unsigned int EBO;
        unsigned int VAO;
        unsigned int VBO;

        std::vector<float> rectangle_vertices = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };
    
        std::vector<unsigned int> indices = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
};

//3D PRIMITIVES
class Cube {
    public:
        Cube();
        void render(Shader shader, const ICamera &camera);
        void add_texture(const char *file);

    public:
        Transform transform;
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int texture;
        //pos 3 //texture coords 2 // normal 3
        std::vector<float> vertices
        {
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 0.0f,    0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,    0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,    0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,    0.0f, 0.0f, 1.0f, 
            0.5f, -0.5f, 0.5f,     1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,      1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,      1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,     0.0f, 1.0f,    0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,    0.0f, 0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    -1.0f, 0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    -1.0f, 0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    -1.0f, 0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    -1.0f, 0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,    -1.0f, 0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    -1.0f, 0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    1.0f, 0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    1.0f, 0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    1.0f, 0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    1.0f, 0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,    0.0f, 0.0f,    1.0f, 0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    1.0f, 0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f,    0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,    0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, -1.0f,  0.0f,

            -0.5f, 0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 1.0f,  0.0f, 
            0.5f, 0.5f, -0.5f,     1.0f, 1.0f,    0.0f, 1.0f,  0.0f,
            0.5f, 0.5f, 0.5f,      1.0f, 0.0f,    0.0f, 1.0f,  0.0f,
            0.5f, 0.5f, 0.5f,      1.0f, 0.0f,    0.0f, 1.0f,  0.0f,
            -0.5f, 0.5f, 0.5f,     0.0f, 0.0f,    0.0f, 1.0f,  0.0f,
            -0.5f, 0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 1.0f,  0.0f
        };
};

#endif