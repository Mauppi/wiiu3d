#include "animation.h"

#include "app.h"
#include <whb/log.h>

void Animation::init(float start, float end, float duration) {
    WHBLogPrint("Animation::init()...");

    startTime = start;
    endTime = end;
    DurTime = duration;
    progress = 0.0f;
    finished = false;

    user_init();
}

void Animation::play() {
    finished = false;
    playing = true;
}

void Animation::stop() {
    playing = false;
}

void Animation::update() {
    if (finished || !playing) {
        return;
    }

    startProgress += deltaTime;
    if (startProgress >= startTime) {
        progress += deltaTime / DurTime;
    }

    if (progress >= 1.0f) {
        progress = 1.0f;
        finished = true;
    }

    user_update(progress);

}

void Animation::deinit() {
    WHBLogPrint("Animation::deinit()...");

    user_deinit();
}

Animation::~Animation() {
    WHBLogPrint("Animation::~Animation()...");

    deinit();
}

void AnimationGroup::init() {

}

void AnimationGroup::add_animation(Animation *animation) {
    animations.push_back(animation);
}

void AnimationGroup::deinit() {

    for (Animation* anim : animations) {
        anim->deinit();
    }

    animations.clear();
}

AnimationGroup::~AnimationGroup() {
    deinit();
}

void Sequence::init() {
    finished = false;
}

void Sequence::update() {
    if (finished) {
        return;
    }

    int anims_finished = 0;

    for (Animation* anim : groups[group_index]->animations) {
        anim->update();

        if (anim->finished) {
            anims_finished++;
        }
    }

    if (anims_finished == groups[group_index]->animations.size()) {
        group_index++;
        if (group_index == groups.size()) {
            finished = true;
        }
    }
}

void Sequence::deinit() {
    for (AnimationGroup* group : groups) {
        group->deinit();
    }

    groups.clear();
}

Sequence::~Sequence() {
    deinit();
}

void Sequence::add_group(AnimationGroup *group) {
    groups.push_back(group);
}

void Sequence::play() {
    group_index = 0;
    finished = false;
}

void Sequence::stop() {
    finished = true;
}

void AnimationManager::init() {

}

void AnimationManager::add_animation(Animation *animation) {
    animations.push_back(animation);
}

void AnimationManager::add_sequence(Sequence *sequence) {
    sequences.push_back(sequence);
}

void AnimationManager::update() {

    for (Animation* anim : animations) {
        anim->update();
    }

    for (Sequence* seq : sequences) {
        seq->update();
    }

}

void AnimationManager::deinit() {
    for (Animation* anim : animations) {
        anim->deinit();
    }

    animations.clear();

    for (Sequence* seq : sequences) {
        seq->deinit();
    }

    sequences.clear();
}