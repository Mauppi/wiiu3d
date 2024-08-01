#ifndef INPUT_H
#define INPUT_H

#include <vpad/input.h>

bool input_init();

void input_run();

bool input_vpad_button_down(VPADButtons button);
bool input_vpad_button_up(VPADButtons button);
bool input_vpad_button_pressed(VPADButtons button);

inline bool input_flag_disabled = false;
inline VPADStatus vpad_current_status;

#endif