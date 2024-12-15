#ifndef LEVELSONE_H
#define LEVELSONE_H
#include "engine/sprite.h"
#include "engine/sound.h"
#include "fader.h"

struct LevelMainMenu {
    Sprite *bgSpr;
    Sprite *uibt_jaa_normal;
    Sprite *uibt_jaa_hover;
    Sprite *uibt_play_normal;
    Sprite *uibt_play_hover;
    Sprite *uibt_quit_normal;
    Sprite *uibt_quit_hover;
    Fader *fader;
    AXVoice *vo_intro;
    AXVoice *music;
    AXVoice *sfx_vo_jaa_click;
    AXVoice *sfx_vo_play;
    AXVoice *sfx_vo_quit;
    int ui_index = 0;

    void init();
    void update();
    void draw();
    ~LevelMainMenu();

    private:
        bool first_load_flag = false;
        float fadeTime = 0.0f;
        void play_voice(const char *filename);
        void hover_changed(int index);
};

#endif