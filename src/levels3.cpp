#include "levels3.h"

#include "engine/app.h"

void LevelPuzzle2::init() {
    trump = new Sprite();
    trump->init("trump.gtx");
    trump->position = glm::vec3(-720.0f, -720.0f, 0.3f);
    trump->scale = glm::vec3(340.0f, 380.0f, 1.0f);
    trump->visible = true;

    bg = new Sprite();
    bg->init("tanssi_bg.gtx");
    bg->position = glm::vec3(0.0f, 0.0f, 0.0f);
    bg->scale = glm::vec3(1920.0f, 1080.0f, 1.0f);
    bg->visible = true;

    introtext1 = new Sprite();
    introtext1->init("puzzle2_text1.gtx");
    introtext1->position = glm::vec3(-1920.0f + (1020.0f), 720.0f, 5.5f);
    introtext1->scale = glm::vec3(1020.0f, 80.0f, 1.0f);
    introtext1->colorModulate.w = 0.0f;

    introtext2 = new Sprite();
    introtext2->init("puzzle2_text2.gtx");
    introtext2->position = glm::vec3(-1920.0f + (1636.0f), 150.0f, 5.5f);
    introtext2->scale = glm::vec3(1636.0f, 76.0f, 1.0f);
    introtext2->colorModulate.w = 0.0f;

    introtext3 = new Sprite();
    introtext3->init("puzzle2_text3.gtx");
    introtext3->position = glm::vec3(-1920.0f + (1340.0f), -400.0f, 5.5f);
    introtext3->scale = glm::vec3(1340.0f, 67.0f, 1.0f);
    introtext3->colorModulate.w = 0.0f;

    introtext3end = new Sprite();
    introtext3end->init("puzzle2_text3end.gtx");
    introtext3end->position = glm::vec3(-1920.0f + 2680.0f + 52.0f, -400.0f, 5.5f);
    introtext3end->scale = glm::vec3(52.0f, 67.0f, 1.0f);
    introtext3end->colorModulate.w = 0.0f;

    fader = new Fader();
    fader->init();
    fader->fade_out(0.0f, 255);
    fader->blackSpr->colorModulate.w = 1.0f;

    music1_l = sound_create_voice("Sensationallow.dsp", 0.5f, -1.0f);
    music1_r = sound_create_voice("Sensationallow_2.dsp", 0.5f, 1.0f);
}

void LevelPuzzle2::update() {
    if (!firstLoadFlag) {
        firstLoadFlag = true;
        sound_play_voice(music1_l);
        sound_play_voice(music1_r);
    }

    intro_animtimer += deltaTime;

    if (intro_animtimer >= 1.0f && intro_animstage == 0) {
        intro_animstage = 1;
        introtext1targetalpha = 1.0f;
    } else if (intro_animtimer >= 2.0f && intro_animstage == 1) {
        intro_animstage = 2;
        introtext2targetalpha = 1.0f;
    } else if (intro_animtimer >= 4.0f && intro_animstage == 2) {
        intro_animstage = 3;
        introtext3targetalpha = 1.0f;
    } else if (intro_animtimer >= 7.0f && intro_animstage == 3) {
        intro_animstage = 4;
        introtext3endtargetalpha = 1.0f;
    } else if (intro_animtimer >= 9.5f && intro_animstage == 4) {
        intro_animstage = 5;
        fader->fade_in(3.5f, 0);
        introtext1targetalpha = 0.0f;
        introtext2targetalpha = 0.0f;
        introtext3targetalpha = 0.0f;
        introtext3endtargetalpha = 0.0f;
    }

    if (intro_animtimer >= 132.0f && !musicStopTrigger) {
        musicStopTrigger = true;

        fader->fade_out(5.0f, 255);
    }

    if (intro_animtimer >= 137.0f && !endFadeTrigger) {
        endFadeTrigger = true;
        load_level(LEVEL_MAIN_MENU);
    }

    introtext1->colorModulate.w = lerp(introtext1->colorModulate.w, introtext1targetalpha, deltaTime * 7.0f);
    introtext2->colorModulate.w = lerp(introtext2->colorModulate.w, introtext2targetalpha, deltaTime * 7.0f);
    introtext3->colorModulate.w = lerp(introtext3->colorModulate.w, introtext3targetalpha, deltaTime * 7.0f);
    introtext3end->colorModulate.w = lerp(introtext3end->colorModulate.w, introtext3endtargetalpha, deltaTime * 7.0f);

    fader->update();
}

void LevelPuzzle2::draw() {
    bg->draw();
    trump->draw();
    fader->draw();

    introtext1->draw();
    introtext2->draw();
    introtext3->draw();
    introtext3end->draw();
}

void LevelPuzzle2::draw_drc() {

}

LevelPuzzle2::~LevelPuzzle2() {
    sound_stop_voice(music1_l);
    AXFreeVoice(music1_l);
    sound_stop_voice(music1_r);
    AXFreeVoice(music1_r);
    delete trump;
    delete bg;
    delete fader;
    delete introtext1;
    delete introtext2;
    delete introtext3;
    delete introtext3end;
}