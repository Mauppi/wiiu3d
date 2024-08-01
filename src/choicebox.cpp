#include "choicebox.h"
#include <whb/log.h>
#include "engine/input.h"


void ChoiceBox::init() {
    status = new ChoiceBoxStatus();

    selectSound = sound_create_voice("choice_select.dsp", 0.5f, 0.0f);
    selectSoundDRC = sound_create_voice("choice_select.dsp", 0.5f, 0.0f, AX_DEVICE_TYPE_DRC);
    bg = new Sprite();
    bg->init("texture_black.gtx");
    bg->scale = glm::vec3(1920.0f, 1080.0f, 1.0f);
    bg->colorModulate = glm::vec4(1.0f, 1.0f, 1.0f, 0.4f);
    bg->position = glm::vec3(0.0f, 0.0f, 0.15f);
}

void ChoiceBox::add_choice(const char *image_path) {
    WHBLogPrintf("Pushing choice: %s", image_path);
    choiceBgs.push_back(new Sprite());
    choices.push_back(new Sprite());
    WHBLogPrintf("Added choice: %s", image_path);
    choiceBgs[addedChoices]->init("choicebox_bg.gtx");
    switch(addedChoices % 4)
    {
        case 0:
            choiceBgs[addedChoices]->position = glm::vec3(-960.0f, 360.0f, 0.2f);
            break;
        case 1:
            choiceBgs[addedChoices]->position = glm::vec3(960.0f, 360.0f, 0.2f);
            break;
        case 2:
            choiceBgs[addedChoices]->position = glm::vec3(-960.0f, -360.0f, 0.2f);
            break;
        case 3:
            choiceBgs[addedChoices]->position = glm::vec3(960.0f, -360.0f, 0.2f);
            break;
    }
    choiceBgs[addedChoices]->scale = glm::vec3(460.0f, 180.0f, 1.0f);
    choices[addedChoices]->init(image_path);
    choices[addedChoices]->position = choiceBgs[addedChoices]->position + glm::vec3(0.0f, 0.0f, 0.02f);
    choices[addedChoices]->scale = choiceBgs[addedChoices]->scale * 0.7f;
    addedChoices++;
    WHBLogPrintf("inited choice: %s", image_path);
}
    
ChoiceBoxStatus *ChoiceBox::get_status() {
    return status;
}

void ChoiceBox::update() {

    if (vpad_current_status.tpNormal.touched == 1 && !touchDown) {
        touchDown = true;
        WHBLogPrintf("TP: %d, %d", vpad_current_status.tpNormal.x, vpad_current_status.tpNormal.y);
        if (vpad_current_status.tpNormal.x < 1920 / 2 && vpad_current_status.tpNormal.y < 1080 / 2 && addedChoices >= 2) {
            // LOWER LEFT CORNER
            select(2);
        } else if (vpad_current_status.tpNormal.x < 1920 / 2 && vpad_current_status.tpNormal.y > 1080 / 2 && addedChoices >= 3) {
            // LOWER RIGHT CORNER
            select(3);
        } else if (vpad_current_status.tpNormal.x > 1920 / 2 && vpad_current_status.tpNormal.y < 1080 / 2 && addedChoices >= 0) {
            // UPPER LEFT CORNER
            select(0);
        } else if (vpad_current_status.tpNormal.x > 1920 / 2 && vpad_current_status.tpNormal.y > 1080 / 2 && addedChoices >= 1) {
            // UPPER RIGHT CORNER
            select(1);
        }
    } else if (vpad_current_status.tpNormal.touched == 0 && touchDown) {
        touchDown = false;
    }

}

void ChoiceBox::select(int index) {
    if (status->ready) return;


    sound_play_voice(selectSound);
    if (status->selected == index) {
        sound_play_voice(selectSoundDRC);
        status->ready = true;
    }
    status->selected = index;
}

void ChoiceBox::draw() {
    for (int i = 0; i < addedChoices; i++) {
        choiceBgs[i]->draw();
        choices[i]->draw();
        bg->draw();
    }
}

void ChoiceBox::draw_drc() {
    for (int i = 0; i < addedChoices; i++) {
        choiceBgs[i]->draw();
        choices[i]->draw();
    }
}

ChoiceBox::~ChoiceBox() {
    sound_stop_voice(selectSound);
    AXFreeVoice(selectSound);
    sound_stop_voice(selectSoundDRC);
    AXFreeVoice(selectSoundDRC);
    delete status;
    delete bg;

    for (int i = 0; i < addedChoices; i++) {
        delete choiceBgs[i];
        delete choices[i];
    }
}