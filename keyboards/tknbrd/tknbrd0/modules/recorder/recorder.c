#include "recorder.h"
#include "tknbrd0/custom_keycodes.h"


#define RECORDER_MAX_KEYS 64

static uint16_t record_buffer[RECORDER_MAX_KEYS];
static uint8_t record_length;
//static recorder_state_t state;

void recorder_start(void){
    record_length = 0;
};

void recorder_stop(void){
    //state = REC_STOP;
};

bool recorder_handle_record(uint16_t keycode){
    // if (state != REC_START) {
    //     //forming packet from captured keycodes?
    //     return true;
    // }

    if (record_length >= RECORDER_MAX_KEYS) {
        return false;
    }

    record_buffer[record_length++] = keycode;
    return false;
};
