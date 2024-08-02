#include "levels2.h"
#include <whb/log.h>
#include "engine/app.h"
#include "engine/resourcemanager.h"
#include "engine/sound.h"

void LevelPuzzle1::init() {
    WHBLogPrint("LevelPuzzle1::init()");

    vo_intro = sound_create_voice("puzzle1_intro.dsp");
    mus_selecting_l = sound_create_voice("intensewait.dsp", 0.7f, -1.0f);
    mus_selecting_r = sound_create_voice("intensewait_2.dsp", 0.7f, 1.0f);
    mus_selecting_l_drc = sound_create_voice("intensewait_drc.dsp", 0.7f, 0.0f, AX_DEVICE_TYPE_DRC);

    trump = new Sprite();
    trump->init("trump.gtx");
    trump->position = glm::vec3(-2600.0f, -720.0f, 0.0f);
    trump->scale = glm::vec3(340.0f, 380.0f, 1.0f);
    trump->visible = true;

    bullet = new Sprite();
    bullet->init("bullet.gtx");
    bullet->position = glm::vec3(0.0f, 0.0f, 0.0f);
    bullet->scale = glm::vec3(64.0f, 64.0f, 1.0f);
    bullet->visible = false;

    sniper = new Sprite();
    sniper->init("pewpewman.gtx");
    sniper->position = glm::vec3(720.0f, -1920.0f, 0.0f);
    sniper->scale = glm::vec3(340.0f, 380.0f, 1.0f);
    sniper->visible = false;

}

void LevelPuzzle1::update() {
    if (!initial_load_flag) {
        sound_play_voice(vo_intro);
        initial_load_flag = true;
    }

    introanimtimer += deltaTime;
    if (introanimtimer >= 1.5f && introanimindex == 0) {
        introanimindex = 1;
    } else if (introanimtimer >= 6.0f && introanimindex == 1) {
        introanimindex = 2;
    } else if (introanimtimer >= 8.0f && introanimindex == 2) {
        introanimindex = 3;
        
        sniper->visible = true;
    }

    if (introanimindex == 0) {
        trump->position.x = lerp(trump->position.x, -1600.0f, 1.0f * deltaTime);
    } else if (introanimindex == 1) {
        trump->position.x = lerp(trump->position.x, -1080.0f, 1.0f * deltaTime);
        trump->position.y = lerp(trump->position.y, -720.0f, 1.0f * deltaTime);
    } else if (introanimindex == 2) {
        trump->position.x = lerp(trump->position.x, -720.0f, 1.0f * deltaTime);
    } else if (introanimindex == 3) {
        sniper->position.y = lerp(sniper->position.y, -720.0f, 5.0f * deltaTime);
    }

    if (selecting_started) {
        choicebox->update();
    }

    if (introanimtimer >= 13.25f && !selecting_started) {
        selecting_started = true;

        sound_play_voice(mus_selecting_l);
        sound_play_voice(mus_selecting_r);
        sound_play_voice(mus_selecting_l_drc);
        drc_lookup_flag = false;
        choicebox = new ChoiceBox();
        choicebox->init();
        choicebox->add_choice("puzzle1_choice1.gtx");
        choicebox->add_choice("pewpewman.gtx");
        choicebox->add_choice("puzzle1_choice1.gtx");
        choicebox->add_choice("pewpewman.gtx");
    }
}

void LevelPuzzle1::draw() {
    if (selecting_started) {
        choicebox->draw();
    }
    trump->draw();
    bullet->draw();
    sniper->draw();
}

void LevelPuzzle1::draw_drc() {
    if (selecting_started) {
        choicebox->draw_drc();
    }
}

LevelPuzzle1::~LevelPuzzle1() {
    sound_stop_voice(mus_selecting_l);
    AXFreeVoice(mus_selecting_l);
    sound_stop_voice(mus_selecting_r);
    AXFreeVoice(mus_selecting_r);
    sound_stop_voice(mus_selecting_l_drc);
    AXFreeVoice(mus_selecting_l_drc);
    sound_stop_voice(vo_intro);
    AXFreeVoice(vo_intro);

    delete trump;
    delete bullet;
    delete sniper;

    ResourceManager_FreeResource("trump.gtx");
    ResourceManager_FreeResource("bullet.gtx");
    ResourceManager_FreeResource("sniper.gtx");
}