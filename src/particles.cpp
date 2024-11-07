#include "particles.h"
#include "engine/app.h"

#include <whb/log.h>

Particle::~Particle()
{
    if (sprite)
    {
        delete sprite;
    }
}

void ParticleSystem::emit(glm::vec3 position, glm::vec3 velocity, glm::vec4 color, float lifetime) {
    Particle *p = new Particle;
    if (sprite) {
        p->sprite = sprite;
    }
    p->position = position;
    p->velocity = velocity;
    p->color = color;
    p->lifetime = lifetime;
    particles.push_back(p);
}

void ParticleSystem::init() {
    WHBLogPrint("ParticleSystem::init()");

    emit_timer = emit_rate;
}

void ParticleSystem::update() {

    if (auto_emitting) {
        emit_timer -= deltaTime;
        if (emit_timer <= 0.0f) {
            emit(emit_position, emit_velocity, emit_color, emit_lifetime);
            emit_timer = emit_rate;
        }
    }

    for (int i = 0; i < particles.size(); i++) {
        if (particles[i]->lifetime <= 0.0f) {
            delete particles[i];
            particles.erase(particles.begin() + i);
            i--;
        } else {
            particles[i]->position += particles[i]->velocity;
            particles[i]->lifetime -= deltaTime;
        }
    }
}

void ParticleSystem::draw() {
    for (int i = 0; i < particles.size(); i++) {
        if (particles[i]->sprite) {
            particles[i]->sprite->position = particles[i]->position;
            particles[i]->sprite->scale = emit_scale;
            particles[i]->sprite->draw();
        }
    }
}

ParticleSystem::~ParticleSystem() {
    for (int i = 0; i < particles.size(); i++) {
        delete particles[i];
    }
}