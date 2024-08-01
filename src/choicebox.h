#ifndef CHOICEBOX_H
#define CHOICEBOX_H

#define CHOICEBOX_MAX_CHOICES = 4

#include "engine/sprite.h"
#include "engine/sound.h"
#include <vector>

struct ChoiceBoxStatus {
    bool ready = false;
    int selected = 0;  
};

struct ChoiceBox {

    Sprite *bg;
    std::vector<Sprite*> choices;
    std::vector<Sprite*> choiceBgs;
    ChoiceBoxStatus *status;
    AXVoice *selectSound;
    AXVoice *selectSoundDRC;
    int addedChoices = 0;
    int selected = -1;

    void init();
    void add_choice(const char *image_path);
    ChoiceBoxStatus *get_status();
    void update();
    void draw();
    void draw_drc();
    ~ChoiceBox();

    private:
        bool touchDown = false;
        void select(int index);
};

#endif