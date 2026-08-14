#include "recorder.h"

static recorder_state_t state;

void recorder_start(void){
    state = REC_START;
};

void recorder_stop(void){
    state = REC_STOP;
};

void recorder_handle_record(uint16_t keycode){
    //do things
};
