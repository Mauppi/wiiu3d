#include "levels3.h"

void LevelPuzzle2::init() {
    trump = new Sprite();
    trump->init("trump.gtx");
    trump->position = glm::vec3(-2600.0f, -720.0f, 0.0f);
    trump->scale = glm::vec3(340.0f, 380.0f, 1.0f);
    trump->visible = true;

    bg = new Sprite();
    bg->init("tanssi_bg.gtx");
    bg->scale = glm::vec3(1920.0f, 1080.0f, 1.0f);
    bg->position = glm::vec3(0.0f, 0.0f, -1.0f);
    bg->visible = true;

    fader = new Fader();
    fader->init();
}

void LevelPuzzle2::update() {
    if (!firstLoadFlag) {
        firstLoadFlag = true;
    }

    fader->update();
}

void LevelPuzzle2::draw() {
    trump->draw();
    bg->draw();
    fader->draw();
}

void LevelPuzzle2::draw_drc() {

}

LevelPuzzle2::~LevelPuzzle2() {
    delete trump;
    delete bg;
    delete fader;
}