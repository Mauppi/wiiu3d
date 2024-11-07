#include "levels1.h"
#include <whb/log.h>
#include "engine/input.h"
#include "engine/app.h"
#include "engine/resourcemanager.h"



void LevelMainMenu::init() {
    WHBLogPrintf("LevelMainMenu init");

    bgSpr = new Sprite();
    uibt_play_normal = new Sprite();
    uibt_play_hover = new Sprite();
    uibt_jaa_normal = new Sprite();
    uibt_jaa_hover = new Sprite();
    uibt_quit_normal = new Sprite();
    uibt_quit_hover = new Sprite();
    fader = new Fader();


    bgSpr->init("texture_main_menu_bg.gtx");
    bgSpr->scale = glm::vec3(1920.0f, 1080.0f, 1.0f);
    bgSpr->position = glm::vec3(0.0f, 0.0f, 0.0f);
    bgSpr->visible = true;

    uibt_play_normal->init("texture_main_menu_play_button_normal.gtx");
    uibt_play_normal->scale = glm::vec3(360.0f, 90.0f, 1.0f);
    uibt_play_normal->position = glm::vec3(1200.0f, 500.0f, 0.0f);
    uibt_play_hover->init("texture_main_menu_play_button_hover.gtx");
    uibt_play_hover->position = glm::vec3(1200.0f, 500.0f, 0.0f);
    uibt_play_hover->scale = glm::vec3(360.0f, 90.0f, 1.0f);
    uibt_play_hover->visible = false;
    uibt_jaa_normal->init("texture_main_menu_jaa_button_normal.gtx");
    uibt_jaa_normal->position = glm::vec3(1200.0f, 300.0f, 0.0f);
    uibt_jaa_normal->scale = glm::vec3(360.0f, 90.0f, 1.0f);
    uibt_jaa_hover->init("texture_main_menu_jaa_button_hover.gtx");
    uibt_jaa_hover->position = glm::vec3(1200.0f, 300.0f, 0.0f);
    uibt_jaa_hover->scale = glm::vec3(360.0f, 90.0f, 1.0f);
    uibt_jaa_hover->visible = false;
    uibt_quit_normal->init("texture_main_menu_quit_button_normal.gtx");
    uibt_quit_normal->position = glm::vec3(1200.0f, 0.0f, 0.0f);
    uibt_quit_normal->scale = glm::vec3(360.0f, 90.0f, 1.0f);
    uibt_quit_hover->init("texture_main_menu_quit_button_hover.gtx");
    uibt_quit_hover->position = glm::vec3(1200.0f, 0.0f, 0.0f);
    uibt_quit_hover->scale = glm::vec3(360.0f, 90.0f, 1.0f);
    uibt_quit_hover->visible = false;

    fader->init();

    vo_intro = sound_create_voice("tervetuloa.dsp", 0.5f, 0.0f, AX_DEVICE_TYPE::AX_DEVICE_TYPE_TV);

    music = sound_create_voice("staying.dsp", 0.5f, 0.0f, AX_DEVICE_TYPE::AX_DEVICE_TYPE_TV);

    if (lvlchange_fade_in_flag) {
        fader->fade_in(1.0f, 0);
    }
}

void LevelMainMenu::play_voice(const char *soundFile) {
    sound_stop_voice(vo_intro);
    AXFreeVoice(vo_intro);

    vo_intro = sound_create_voice(soundFile, 0.5f, 0.0f, AX_DEVICE_TYPE::AX_DEVICE_TYPE_TV);

    sound_play_voice(vo_intro);
}

void LevelMainMenu::hover_changed(int index) {

    uibt_quit_normal->visible = false;
    uibt_quit_hover->visible = false;
    uibt_jaa_normal->visible = false;
    uibt_jaa_hover->visible = false;
    uibt_play_normal->visible = false;
    uibt_play_hover->visible = false;

    if (ui_index == 0) {
        play_voice("main_menu_play_hover.dsp");
        uibt_play_hover->visible = true;
        uibt_jaa_normal->visible = true;
        uibt_quit_normal->visible = true;
    } else if (ui_index == 1) {
        // NO VOICE IDK
        uibt_play_normal->visible = true;
        uibt_jaa_hover->visible = true;
        uibt_quit_normal->visible = true;
    } else if (ui_index == 2) {
        play_voice("main_menu_quit_hover.dsp");
        uibt_play_normal->visible = true;
        uibt_jaa_normal->visible = true;
        uibt_quit_hover->visible = true;
    }
}

void LevelMainMenu::update() {
    if (!first_load_flag) {
        first_load_flag = true;
        sound_play_voice(vo_intro);
        sound_play_voice(music);
        uibt_play_hover->visible = true;
        uibt_play_normal->visible = false;
    }
    
    fader->update();

    if (fadeTime > 0.0f) {
        fadeTime -= deltaTime;
    } else {
        if (input_flag_disabled) {
            input_flag_disabled = false;
            load_level(LEVEL_PUZZLE1);
            return;
        }
    }

    if (input_vpad_button_down(VPADButtons::VPAD_BUTTON_UP) || input_vpad_button_down(VPADButtons::VPAD_STICK_L_EMULATION_UP)) {
        ui_index -= 1;
        if (ui_index < 0) {
            ui_index = 2;
        }

        hover_changed(ui_index);

    } else if (input_vpad_button_down(VPADButtons::VPAD_BUTTON_DOWN) || input_vpad_button_down(VPADButtons::VPAD_STICK_L_EMULATION_DOWN)) {
        ui_index += 1;
        if (ui_index > 2) {
            ui_index = 0;
        }

        hover_changed(ui_index);
    }

    if (input_vpad_button_down(VPADButtons::VPAD_BUTTON_A)) {
        if (ui_index == 0) {
            input_flag_disabled = true;
            fader->fade_out(3.0f, 255);
            fadeTime = 3.0f;
        } else if (ui_index == 1) {
            play_voice("main_menu_jaa_pressed.dsp");
        } else if (ui_index == 2) {
            app_quit_flag = true;
        }
    }

}

void LevelMainMenu::draw() {
    uibt_play_normal->draw();
    uibt_play_hover->draw();
    uibt_jaa_normal->draw();
    uibt_jaa_hover->draw();
    uibt_quit_normal->draw();
    uibt_quit_hover->draw();
    bgSpr->draw();
    fader->draw();
}

LevelMainMenu::~LevelMainMenu() {
    sound_stop_voice(vo_intro);
    AXFreeVoice(vo_intro);
    sound_stop_voice(music);
    AXFreeVoice(music);
    delete uibt_play_normal;
    delete uibt_play_hover;
    delete uibt_jaa_normal;
    delete uibt_jaa_hover;
    delete uibt_quit_normal;
    delete uibt_quit_hover;
    delete bgSpr;
    delete fader;

    ResourceManager_FreeResource("texture_main_menu_play_button_normal.gtx");
    ResourceManager_FreeResource("texture_main_menu_play_button_hover.gtx");
    ResourceManager_FreeResource("texture_main_menu_jaa_button_normal.gtx");
    ResourceManager_FreeResource("texture_main_menu_jaa_button_hover.gtx");
    ResourceManager_FreeResource("texture_main_menu_quit_button_normal.gtx");
    ResourceManager_FreeResource("texture_main_menu_quit_button_hover.gtx");
    ResourceManager_FreeResource("texture_main_menu_bg.gtx");
    
    WHBLogWrite("LevelMainMenu destroyed");
}