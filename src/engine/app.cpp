#include "app.h"
#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>
#include <whb/log_cafe.h>
#include <sysapp/launch.h>
#include <coreinit/time.h>
#include <coreinit/thread.h>
#include "graphics.h"
#include "input.h"



bool app_init() {

    WHBProcInit();
    WHBLogCafeInit();
    graphics_init();
    WHBLogConsoleInit();
    sound_init();
    input_init();

    load_level(LEVEL_MAIN_MENU, true);

    return true;
}

bool app_run() {

    int32_t currentTick = OSGetTime();

    while (WHBProcIsRunning()) {
        
        int32_t newTick = OSGetTime();
        int32_t deltaTick = newTick - currentTick;
        currentTick = newTick;
        deltaTime = OSTicksToMilliseconds(deltaTick) / 1000.0f;
        
        input_run();

        graphics_run();

        level_update();

        //WHBLogConsoleDraw();

        if (app_quit_flag) {
            SYSLaunchMenu();
        }
    }

    app_quit();

    return true;
}

void app_draw() {
    level_draw();
}

void app_draw_drc() {
    level_draw_drc();
}

void app_quit() {

    graphics_exit();

    WHBLogCafeDeinit();
    WHBProcShutdown();
}