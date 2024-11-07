#ifndef PARTICLES_H
#define PARTICLES_H

#include "engine/sprite.h"
#include <vector>

struct Particle {
    Sprite *sprite;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    float lifetime;
    ~Particle();
};

struct ParticleSystem {
    std::vector<Particle*> particles;
    Sprite* sprite;
    bool auto_emitting = false;
    float emit_rate = 0.1f;
    glm::vec3 emit_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 emit_scale = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 emit_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 emit_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    float emit_lifetime = 1.0f;

    void emit(glm::vec3 position, glm::vec3 velocity, glm::vec4 color, float lifetime);

    void init();
    void update();
    void draw();
    ~ParticleSystem();

    private:
        float emit_timer = 0.0f;
};

#endif