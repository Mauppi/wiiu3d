#ifndef LEVELS3_H
#define LEVELS3_H


#include "engine/sprite.h"
#include "engine/sound.h"
#include "fader.h"
#include "choicebox.h"
#include "engine/animation.h"
#include "particles.h"

struct LevelPuzzle2
{
    Sprite *trump;
    Sprite *bg;
    Fader *fader;
    ParticleSystem *rose_particles;
    AXVoice *music1_l;
    AXVoice *music1_r;
    Sprite *introtext1;
    Sprite *introtext2;
    Sprite *introtext3;
    Sprite *introtext3end;

    
    void init();
    void update();
    void draw();
    void draw_drc();
    ~LevelPuzzle2();

    private:
        bool firstLoadFlag = false;
        bool musicStopTrigger = false;
        bool endFadeTrigger = false;
        double intro_animtimer = 0;
        int intro_animstage = 0;
        float introtext1targetalpha = 0.0f;
        float introtext2targetalpha = 0.0f;
        float introtext3targetalpha = 0.0f;
        float introtext3endtargetalpha = 0.0f;
        
};

#endif