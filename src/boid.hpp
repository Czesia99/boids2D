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
        glm::vec2 acceleration = {0.0f, 0.0f};
        float perception_radius = 100;
        glm::vec2 max_steering = {3.0f, 3.0f};
        glm::vec2 min_steering = {3.0f, 3.0f};

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

        void update() {
            for (int i = 0; i < nb_boids; i++)
            {
                boids[i].shape.transform.position.x += boids[i].velocity.x;
                boids[i].shape.transform.position.y += boids[i].velocity.y;

                boids[i].velocity += boids[i].acceleration;

                

                edges(boids[i]);
                align(i, boids);

                boids[i].acceleration = align(i, boids);
                //glm::normalize(boids[i].acceleration);
                //std::cout << "acceleration = " << boids[i].acceleration.x << boids[i].acceleration.y << std::endl;
            }
        }

        void edges(Boid &boid)
        {
            auto &position = boid.shape.transform.position;

            if (position.x >= ctx.win_width)
                position.x -= ctx.win_width;
            else if (position.x < 0)
                position.x += ctx.win_width;

            if (position.y >= ctx.win_height)
                position.y -= ctx.win_height;
            else if (position.y < 0)
                position.y += ctx.win_height;
        }

        glm::vec2 align(int i, std::vector<Boid> &boids)
        {
            glm::vec2 steering;
            glm::vec2 new_steering;
            
            int total = 0;

            for (int j = 0; j < nb_boids; j++)
            {
                float d = glm::distance(boids[i].shape.transform.position, boids[j].shape.transform.position);
                if (i != j && d <= boids[i].perception_radius)
                {
                    steering += boids[j].velocity;
                    total++;
                }
            }
            if (total > 0)
            {
                steering /= total;
                steering -= boids[i].velocity;

                if (steering.x > boids[i].max_steering.x)
                {
                    new_steering.x = boids[i].max_steering.x;
                    //boids[i].velocity.x = boids[i].max_steering.x;
                } else { new_steering.x = steering.x; }
                if (steering.y > boids[i].max_steering.y)
                {
                    new_steering.y = boids[i].max_steering.y;
                } else { new_steering.y = steering.y; }

                if (steering.x < boids[i].min_steering.x)
                {
                    new_steering.x = boids[i].min_steering.x;
                } else {new_steering.x = steering.x;}

                if (steering.y < boids[i].min_steering.y)
                {
                    new_steering.y = boids[i].min_steering.y;
                } else {new_steering.y = steering.y;}


                boids[i].velocity = new_steering;
                
            }
            std::cout << "steering x = " << new_steering.x << "steering y = " << new_steering.y << std::endl;
            return new_steering;
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
            assert(max > min); 
            float random = ((float) rand()) / (float) RAND_MAX;

            float range = max - min;  
            return (random*range) + min;
        }
        
        Context &ctx;
        int nb_boids;
        std::vector<Boid> boids;

    private:
        void create_boids()
        {
            for (int i = 0; i < nb_boids; i++)
            {
                glm::vec2 velocity (random_float(-3, 3), random_float(-3, 3));
                
                glm::vec2 pos(random_float(0, ctx.win_width), random_float(0, ctx.win_height));
                boids.push_back(Boid(pos, velocity));
            }
        }
};