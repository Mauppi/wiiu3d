#include "levelloader.h"
#include <whb/log.h>
#include "engine/app.h"

float drc_lookup_alpha = 0.0f;
bool drc_lookup_direction_flag = true;

void load_level(ELevel level, bool first_load) {
    if (!first_load) {
        switch (current_level) {
            case LEVEL_MAIN_MENU:
                delete main_menu;
                break;
            case LEVEL_PUZZLE1:
                delete puzzle1;
                break;
            case LEVEL_PUZZLE2:
                delete puzzle2;
                break;
            default:
                break;
        }
    } else {
        drc_lookup = new Sprite();
        drc_lookup->init("drc_lookup.gtx");
        drc_lookup->scale = glm::vec3(720.0f, 128.0f, 1.0f);
        //drc_lookup->position = (glm::vec3(1920.0f / 2, 1080.0f / 2, 0.0f));
    }

    switch (level) {
        case LEVEL_MAIN_MENU:
            main_menu = new LevelMainMenu();
            main_menu->init();
            break;
        case LEVEL_PUZZLE1:
            puzzle1 = new LevelPuzzle1();
            puzzle1->init();
            break;
        case LEVEL_ENDING:
            break;
        case LEVEL_PUZZLE2:
            puzzle2 = new LevelPuzzle2();
            puzzle2->init();
            break;
        default:
            level = LEVEL_MAIN_MENU;
            break;
    }

    current_level = level;
}

void level_update() {
    switch (current_level) {
        case LEVEL_MAIN_MENU:
            main_menu->update();
            break;
        case LEVEL_PUZZLE1:
            puzzle1->update();
            break;
        case LEVEL_PUZZLE2:
            puzzle2->update();
            break;
        case LEVEL_ENDING:
            break;
        default:
            break;
    }
}

void level_draw() {
    switch (current_level) {
        case LEVEL_MAIN_MENU:
            main_menu->draw();
            break;
        case LEVEL_PUZZLE1:
            puzzle1->draw();
            break;
        case LEVEL_PUZZLE2:
            puzzle2->draw();
            break;
        case LEVEL_ENDING:
            break;
        default:
            break;
    }
}

void level_draw_drc() {
    if (!drc_lookup_flag) {
        
        switch (current_level)
        {
        case LEVEL_MAIN_MENU:
            break;
        case LEVEL_PUZZLE1:
            puzzle1->draw_drc();
            break;
        case LEVEL_PUZZLE2:
            puzzle2->draw_drc();
            break;
        case LEVEL_ENDING:
            break;
        default:
            break;
        }

        drc_lookup_direction_flag = true;
        drc_lookup_alpha = 0.4f;
        return;
    }

    if (drc_lookup_direction_flag) {
        drc_lookup_alpha += 0.4f * deltaTime;
    } else {
        drc_lookup_alpha -= 0.4f * deltaTime;
    }

    if (drc_lookup_alpha > 1.0f) {
        drc_lookup_alpha = 1.0f;
        drc_lookup_direction_flag = false;
    } else if (drc_lookup_alpha < 0.4f) {
        drc_lookup_alpha = 0.4f;
        drc_lookup_direction_flag = true;
    }

    drc_lookup->colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, drc_lookup_alpha);

    drc_lookup->draw();
}