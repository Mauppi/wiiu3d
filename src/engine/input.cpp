#include "input.h"
#include <whb/log.h>


VPADReadError vpad_error;

bool input_init() {

    VPADInit();

    VPADTouchCalibrationParam *calibParam = new VPADTouchCalibrationParam;

    calibParam->scaleX = 1920.0f;
    calibParam->scaleY = 1080.0f;
    calibParam->adjustX = 0.0f;
    calibParam->adjustY = 0.0f;

    //VPADSetTPCalibrationParam(VPAD_CHAN_0, calibParam);

    return true;
}

void input_run() {

    VPADRead(VPAD_CHAN_0, &vpad_current_status, 1, &vpad_error);
}

bool input_vpad_button_down(VPADButtons button) {

    return (vpad_current_status.trigger & button) != 0 && !input_flag_disabled;
}

bool input_vpad_button_up(VPADButtons button) {

    return (vpad_current_status.release & button) != 0 && !input_flag_disabled;
}
bool input_vpad_button_pressed(VPADButtons button) {

    return (vpad_current_status.hold & button) != 0 && !input_flag_disabled;
}