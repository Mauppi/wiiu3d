#ifndef SPRITE_H
#define SPRITE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <whb/gfx.h>

struct Sprite
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    bool visible = true;

    GX2Texture *texture;
    GX2Sampler sampler = {0};

    bool init(const char* filename);
    void draw();
    ~Sprite();
};

#endif