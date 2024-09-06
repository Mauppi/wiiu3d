#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

struct Animation {
    void init(float start, float end, float time);
    void update();
    void deinit();
    void play();
    void stop();
    ~Animation();

    float startTime = 0.0f;
    float endTime = 0.0f;
    float DurTime = 0.0f;
    float progress = 0.0f;
    float startProgress = 0.0f;

    bool finished = false;
    bool playing = false;
    
    virtual void user_init(){};
    virtual void user_update(float progress){};
    virtual void user_deinit(){};
};

struct AnimationGroup {
    std::vector<Animation*> animations;

    void init();
    void add_animation(Animation* anim);
    void deinit();
    ~AnimationGroup();
};

struct Sequence {
    std::vector<AnimationGroup*> groups;
    void init();
    void update();
    void deinit();
    ~Sequence();

    void add_group(AnimationGroup* group);
    void play();
    void stop();

    bool finished = false;
    int group_index = 0;
};

struct AnimationManager {
    std::vector<Animation*> animations;
    std::vector<Sequence*> sequences;

    void init();
    void add_animation(Animation* anim);
    void add_sequence(Sequence* seq);
    void update();
    void deinit();
};

#endif