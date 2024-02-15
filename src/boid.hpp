#pragma once

#include "kore/shape.hpp"
#include "kore/transform.hpp"
#include "kore/shader.h"
#include "kore/ICamera.hpp"
#include "kore/context.hpp"

#include <glm/gtc/random.hpp>
#include <math.h>

struct Boid {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 velocity = {0.0f, 0.0f};
    glm::vec2 acceleration = {0.0f, 0.0f};
    float perception_radius = 75;
};

class BoidManager {
    public:
        BoidManager(Context &ctx, int nb = 20) : ctx(ctx), nb_boids(nb) {
            srand (time(NULL));
            create_boids();
        };

        void render(Shader shader, const ICamera &camera)
        {
            shape.transform.scale = glm::vec3 {20.0f, 20.0f, 20.0f};

            for (int i = 0; i < nb_boids; i++)
            {
                shape.transform.position.x = boids[i].position.x;
                shape.transform.position.y = boids[i].position.y;
                shape.transform.rotation.z = atan2(boids[i].velocity.y, boids[i].velocity.x) - M_PI/2.0f;
                shape.render(shader, camera);
            }
        }

        void update() {
            for (int i = 0; i < nb_boids; i++)
            {
                glm::vec2 sep = separation(i, boids) * 0.3f;
                glm::vec2 ali = align(i, boids) * 0.01f;
                glm::vec2 coh = cohesion(i, boids) * 0.004f;
                boids[i].acceleration = {0.0f, 0.0f};
                boids[i].acceleration = sep + ali + coh;
                boids[i].velocity += boids[i].acceleration;
                boids[i].velocity = glm::normalize(boids[i].velocity) * 3.0f;

                boids[i].position.x += boids[i].velocity.x;
                boids[i].position.y += boids[i].velocity.y;

                edges(boids[i]);
            }
        }

    private:
        Context &ctx;
        int nb_boids;
        std::vector<Boid> boids;
        Triangle shape;

        glm::vec2 align(int i, std::vector<Boid> &boids)
        {
            glm::vec2 steering;
            int total = 0;

            for (int j = 0; j < nb_boids; j++)
            {
                float d = glm::distance(boids[i].position, boids[j].position);
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
            }
            return steering;
        }

        glm::vec2 separation(int i, std::vector<Boid> boids)
        {
            glm::vec2 steering;
            int total = 0;

            for (int j = 0; j < nb_boids; j++)
            {
                glm::vec2 diff = (boids[i].position - boids[j].position);
                float d = glm::length(diff);

                if (i != j && d <= boids[i].perception_radius)
                {
                    diff /= d;
                    steering += diff;
                    total++;
                }
            }
            if (total > 0)
            {
                steering /= total;
                steering -= boids[i].velocity;
            }
            return steering;
        }

        glm::vec2 cohesion(int i, std::vector<Boid> boids)
        {
            glm::vec2 steering;
            int total = 0;

            for (int j = 0; j < nb_boids; j++)
            {
                float d = glm::distance(boids[i].position, boids[j].position);
                if (i != j && d <= boids[i].perception_radius)
                {
                    steering += boids[j].position;
                    total++;
                }
            }
            if (total > 0)
            {
                steering /= total;
                steering -= boids[i].position;
                steering -= boids[i].velocity;
            }
            return steering;
        }

        void edges(Boid &boid)
        {
            auto &position = boid.position;

            if (position.x >= ctx.win_width)
                position.x -= ctx.win_width;
            else if (position.x < 0)
                position.x += ctx.win_width;

            if (position.y >= ctx.win_height)
                position.y -= ctx.win_height;
            else if (position.y < 0)
                position.y += ctx.win_height;
        }

        float random_float(float min, float max)
        {
            assert(max > min); 
            float random = ((float) rand()) / (float) RAND_MAX;

            float range = max - min;  
            return (random*range) + min;
        }

        void create_boids()
        {
            for (int i = 0; i < nb_boids; i++)
            {
                glm::vec2 pos(random_float(0, ctx.win_width), random_float(0, ctx.win_height));
                glm::vec2 velocity = glm::circularRand(5.0f);
                Boid b;
                b.position = pos;
                b.velocity = velocity;
                boids.push_back(b);
            }
        }
};