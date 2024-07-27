#include "app.h"
#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>
#include <sysapp/launch.h>
#include "sound.h"
#include <whb/gfx.h>
#include <gx2/clear.h>
#include <gx2/draw.h>
#include <gx2/swap.h>
#include <coreinit/time.h>
#include <coreinit/thread.h>

bool app_init() {

    WHBProcInit();
    WHBLogConsoleInit();
    WHBGfxInit();

    test_sound();

    return true;
}

bool app_run() {

    while (WHBProcIsRunning()) {
        

        WHBLogConsoleDraw();

        if (app_quit_flag) {
            SYSLaunchMenu();
        }

        OSSleepTicks(OSMillisecondsToTicks(16));
    }

    app_quit();

    return true;
}

void app_quit() {

    WHBProcShutdown();
}