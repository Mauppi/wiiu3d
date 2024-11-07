#include "fader.h"
#include <whb/log.h>
#include "engine/app.h"

void Fader::init() {
    blackSpr = new Sprite;
    blackSpr->init("texture_black.gtx");
    blackSpr->scale = glm::vec3(1920.0f, 1080.0f, 1.0f);
    blackSpr->position = glm::vec3(0.0f, 0.0f, 0.3f);
    blackSpr->visible = true;
    blackSpr->colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
}

void Fader::fade_in(float time, int a) {
    this->time = time;
    t = 0.0f;
    blackSpr->colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    targetModulate = glm::vec4(0.0f, 0.0f, 0.0f, a / 255.0f);
}

void Fader::fade_out(float time, int a) {
    this->time = time;
    t = 0.0f;
    blackSpr->colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    targetModulate = glm::vec4(0.0f, 0.0f, 0.0f, a / 255.0f);
}

void Fader::update() {
    if (time > 0.0f) {
        
        blackSpr->colorModulate.w = glm::mix(blackSpr->colorModulate.w, targetModulate.w, t);
        t = deltaTime / time;
        time -= deltaTime;
        
    } else {
        blackSpr->colorModulate = targetModulate;
    }
}

void Fader::draw() {
    //WHBLogPrintf("Sprite: %f %f %f %f", blackSpr->colorModulate.x, blackSpr->colorModulate.y, blackSpr->colorModulate.z, blackSpr->colorModulate.w);
    blackSpr->draw();
}