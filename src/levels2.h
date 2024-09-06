#ifndef LEVELS2_H
#define LEVELS2_H

#include "engine/sprite.h"
#include "engine/sound.h"
#include "fader.h"
#include "choicebox.h"
#include "engine/animation.h"

struct LevelPuzzle1
{
    Sprite *trump;
    Sprite *sniper;
    Sprite *bullet;
    Sprite *cough;
    Sprite *grave;

    ChoiceBox *choicebox;

    AXVoice *vo_intro;
    AXVoice *mus_selecting_l;
    AXVoice *mus_selecting_l_drc;
    AXVoice *mus_selecting_r;
    AXVoice *sfx_coughdie;
    AXVoice *sfx_sigma;

    Fader *fader;

    void init();
    void update();
    void draw();
    void draw_drc();
    ~LevelPuzzle1();

    private:
        Animation *choice0_anim_1;
        Animation *choice0_anim_2;
        AnimationGroup *choice0_anim_group1;
        AnimationGroup *choice0_anim_group2;
        Sequence *choice0_anim_seq;
        bool initial_load_flag = false;
        float introanimtimer = 0.0f;
        int introanimindex = 0;
        bool selecting_started = false;
        bool selecting_finished = false;
        int selectedChoice = -1;
        int choiceAnimIndex = 0;
        float choiceAnimTimer = 0.0f;
        
};

#endif