#pragma once

#include "kore/shape.hpp"
#include "kore/transform.hpp"
#include "kore/shader.h"
#include "kore/ICamera.hpp"
#include "kore/context.hpp"

class Boid {
    public:
        Triangle shape;
        

        glm::vec2 velocity = {0.0f, 0.0f};
        //float velocity = 3.0f;
        float acceleration = 0.0f;

        Boid(glm::vec2 pos = glm::vec2(0.0f, 0.0f), glm::vec2 vel = glm::vec2(0.0f, 0.0f)) {
            velocity = vel;
            shape.transform.position.x = pos.x;
            shape.transform.position.y = pos.y;
            shape.transform.scale += 20;
        };
    
    private:
        //Transform transform;     
};

class BoidManager {
    public:

        BoidManager(Context &ctx, int nb = 20) : ctx(ctx), nb_boids(nb) {
            srand (time(NULL));
            create_boids();
        };


        void create_boids()
        {
            for (int i = 0; i < nb_boids; i++)
            {
                glm::vec2 velocity (random_float(-3, 3), random_float(-3, 3));
                
                glm::vec2 pos(random_float(0, ctx.win_width), random_float(0, ctx.win_height));
                boids.push_back(Boid(pos, velocity));
            }
        }

        void update() {
            for (int i = 0; i < nb_boids; i++)
            {
                boids[i].shape.transform.position.x += boids[i].velocity.x;
                boids[i].shape.transform.position.y += boids[i].velocity.y;
                boids[i].velocity += boids[i].acceleration;
                
                if (boids[i].shape.transform.position.x >= ctx.win_width)
                {
                    boids[i].shape.transform.position.x = 0;
                }
                if (boids[i].shape.transform.position.y >= ctx.win_height)
                {
                    boids[i].shape.transform.position.y = 0;
                }
            }
        }

        void render(Shader shader, const ICamera &camera)
        {
            for (int i = 0; i < nb_boids; i++)
            {
                boids[i].shape.render(shader, camera);
            }
        }

        float random_float(float min, float max)
        {
            // this  function assumes max > min, you may want 
            // more robust error checking for a non-debug build
            assert(max > min); 
            float random = ((float) rand()) / (float) RAND_MAX;

            // generate (in your case) a float between 0 and (4.5-.78)
            // then add .78, giving you a float between .78 and 4.5
            float range = max - min;  
            return (random*range) + min;
        }
        
        Context &ctx;
        int nb_boids;
        std::vector<Boid> boids;
        float width;
        float height;
};