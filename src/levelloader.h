#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H
#include "levels1.h"
#include "levels2.h"

enum ELevel {
    LEVEL_MAIN_MENU,
    LEVEL_PUZZLE1,
    LEVEL_ENDING
};

inline ELevel current_level = LEVEL_MAIN_MENU;
inline LevelMainMenu *main_menu;
inline LevelPuzzle1 *puzzle1;
inline Sprite *drc_lookup;
inline bool drc_lookup_flag = true;
inline bool lvlchange_fade_in_flag = false;

void load_level(ELevel level, bool first_load = false);
void level_update();
void level_draw();
void level_draw_drc();

#endif