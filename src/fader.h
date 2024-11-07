#ifndef FADER_H
#define FADER_H

#include "engine/sprite.h"

struct Fader {
    Sprite *blackSpr;

    void init();
    void fade_in(float time, int a);
    void fade_out(float time, int a);
    void update();
    void draw();

    private:
        glm::vec4 targetModulate = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        float time = 0.0f;
        float t = 0.0f;
};

#endif