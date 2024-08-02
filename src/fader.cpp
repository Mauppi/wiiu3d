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
    blackSpr->colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    targetModulate = glm::vec4(0.0f, 0.0f, 0.0f, a / 255.0f);
}

void Fader::fade_out(float time, int a) {
    this->time = time;
    blackSpr->colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    targetModulate = glm::vec4(0.0f, 0.0f, 0.0f, a / 255.0f);
}

void Fader::update() {
    if (time > 0.0f) {
        time -= deltaTime;
        if (blackSpr->colorModulate.w < targetModulate.w) {
            blackSpr->colorModulate.w += deltaTime / time * (targetModulate.w - blackSpr->colorModulate.w);
        } else if (blackSpr->colorModulate.w > targetModulate.w) {
            blackSpr->colorModulate.w -= deltaTime / time * (blackSpr->colorModulate.w - targetModulate.w);
        }
        WHBLogPrintf("Log alpha: %f", blackSpr->colorModulate.w);
    }
}

void Fader::draw() {
    //WHBLogPrintf("Sprite: %f %f %f %f", blackSpr->colorModulate.x, blackSpr->colorModulate.y, blackSpr->colorModulate.z, blackSpr->colorModulate.w);
    blackSpr->draw();
}