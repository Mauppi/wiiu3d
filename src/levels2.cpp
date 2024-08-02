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
    sfx_coughdie = sound_create_voice("coughdie.dsp", 0.5f, 0.0f, AX_DEVICE_TYPE_TV);
    sfx_sigma = sound_create_voice("sigmawin.dsp", 1.0f, 0.0f, AX_DEVICE_TYPE_TV);

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

    cough = new Sprite();
    cough->init("cough_man.gtx");
    cough->position = glm::vec3(720.0f, -720.0f, 0.0f);
    cough->scale = glm::vec3(340.0f, 380.0f, 1.0f);
    cough->visible = false;

    grave = new Sprite();
    grave->init("grave.gtx");
    grave->position = glm::vec3(720.0f, -720.0f, 0.0f);
    grave->scale = glm::vec3(128.0f, 164.0f, 1.0f);
    grave->visible = false;
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

    if (selecting_finished) {
        choiceAnimTimer += deltaTime;
        if (selectedChoice == 0) {
            if (choiceAnimTimer >= 0.1f && choiceAnimIndex == 0) {
                choiceAnimIndex = 1;
                sniper->visible = false;
                cough->visible = true;
            } else if (choiceAnimTimer >= 0.3f && choiceAnimIndex == 1) {
                choiceAnimIndex = 2;
                cough->visible = false;
                sniper->visible = true;
            } else if (choiceAnimTimer >= 0.5f && choiceAnimIndex == 2) {
                choiceAnimIndex = 3;
                sniper->visible = false;
                cough->visible = true;
            } else if (choiceAnimTimer >= 0.7f && choiceAnimIndex == 3) {
                choiceAnimIndex = 4;
                cough->visible = false;
                sniper->visible = true;
            } else if (choiceAnimTimer >= 0.825f && choiceAnimIndex == 4) {
                choiceAnimIndex = 5;
                cough->visible = true;
                sniper->visible = false;
            } else if (choiceAnimTimer >= 1.0f && choiceAnimIndex == 5) {
                choiceAnimIndex = 6;
                cough->visible = false;
                sniper->visible = true;
            } else if (choiceAnimTimer >= 1.7f && choiceAnimIndex == 6) {
                choiceAnimIndex = 7;
                sniper->visible = false;
                cough->visible = true;
            } else if (choiceAnimTimer >= 2.0f && choiceAnimIndex == 7) {
                cough->visible = false;
                sniper->visible = true;
                choiceAnimIndex = 8;
            } else if (choiceAnimTimer >= 2.2f && choiceAnimIndex == 8) {
                sniper->visible = false;
                cough->visible = true;
                choiceAnimIndex = 9;
            } else if (choiceAnimTimer >= 2.4f && choiceAnimIndex == 9) {
                cough->visible = false;
                sniper->visible = true;
                choiceAnimIndex = 10;
            } else if (choiceAnimTimer >= 2.6f && choiceAnimIndex == 10) {
                sniper->visible = false;
                cough->visible = true;
                choiceAnimIndex = 11;
            } else if (choiceAnimTimer >= 2.7f && choiceAnimIndex == 11) {
                cough->visible = false;
                sniper->visible = true;
                choiceAnimIndex = 12;
            } else if (choiceAnimTimer >= 4.0f && choiceAnimIndex == 12) {
                grave->visible = true;
                choiceAnimIndex = 13;
                cough->visible = false;
                sniper->visible = false;
            } else if (choiceAnimTimer >= 6.0f && choiceAnimIndex == 13) {
                choiceAnimIndex = 14;
                sound_play_voice(sfx_sigma);
            }
        }
    }

    if (selecting_started && !selecting_finished) {
        choicebox->update();

        if (choicebox->get_status()->ready) {
            selecting_finished = true;

            sound_stop_voice(mus_selecting_l);
            sound_stop_voice(mus_selecting_r);
            sound_stop_voice(mus_selecting_l_drc);

            selectedChoice = choicebox->get_status()->selected;

            if (selectedChoice == 0) {
                sound_play_voice(sfx_coughdie);
            }

            drc_lookup_flag = true;
        }
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
    }
}

void LevelPuzzle1::draw() {
    trump->draw();
    bullet->draw();
    sniper->draw();
    cough->draw();
    grave->draw();
    if (selecting_started && !selecting_finished) {
        choicebox->draw();
    }
}

void LevelPuzzle1::draw_drc() {
    if (selecting_started && !selecting_finished) {
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