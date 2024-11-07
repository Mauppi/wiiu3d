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

    
    void init();
    void update();
    void draw();
    void draw_drc();
    ~LevelPuzzle2();

    private:
        bool firstLoadFlag = false;
};

#endif