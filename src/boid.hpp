#pragma once

#include "kore/shape.hpp"
#include "kore/transform.hpp"
#include "kore/shader.h"
#include "kore/ICamera.hpp"

class Boid {

    public:
        Boid(glm::vec2 pos = glm::vec2(0.0f, 0.0f)){
            position = pos;
        };

        void render(Shader shader, const ICamera &camera) {
            shape.render(shader, camera);
        };
    
        Triangle shape;
        Transform &transform = shape.transform;
        float acceleration = 100.0f;
        float velocity = 3.0f;
        glm::vec2 position;
    private:
        //Transform transform;
        
        
};