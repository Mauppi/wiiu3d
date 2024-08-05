#ifndef APP_H
#define APP_H
#include <typeinfo>
#include "sprite.h"
#include "../levelloader.h"
#include "animation.h"

inline bool app_quit_flag = false;
inline float deltaTime = 0.0f;
inline AnimationManager animationManager;

template<typename T>
inline T lerp(T a, T b, float t) {
    return a + t * (b - a);
}

inline unsigned int assertti(std::size_t x) {
    if (x == 0) {
        app_quit_flag = true;
    }
    return x;
}

bool app_init();
bool app_run();
void app_draw();
void app_draw_drc();
void app_quit();

#endif