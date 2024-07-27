#ifndef APP_H
#define APP_H

inline bool app_quit_flag = false;

bool app_init();
bool app_run();
void app_quit();

#endif