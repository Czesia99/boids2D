#pragma once

#include "kore/shape.hpp"
#include "kore/transform.hpp"
#include "kore/shader.h"
#include "kore/ICamera.hpp"
#include "kore/context.hpp"

class Boid {
    public:
        Triangle shape;
        Transform &transform = shape.transform;
        float acceleration = 0.0f;
        float velocity = 3.0f;
        glm::vec2 position;

        Boid(glm::vec2 pos = glm::vec2(0.0f, 0.0f)) : position(pos){
            transform.position.x = pos.x;
            transform.position.y = pos.y;
        };

        void render(Shader shader, const ICamera &camera) {
            shape.render(shader, camera);
        };
    

    private:
        //Transform transform;
        
        
};