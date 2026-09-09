#include "recorder.h"
#include "tknbrd0/custom_keycodes.h"
#include "quantum/keycodes.h"


#define RECORDER_MAX_KEYS 64

static recorder_entry_t record_buffer[RECORDER_MAX_KEYS];
static uint8_t record_length;

void recorder_start(void){
    record_length = 0;
};

void recorder_stop(void){
    //TODO: user notification that record stopped, or could it be autoreset?
    recorder_process_buffer(record_buffer, record_length);
    record_length = 0;
};

// the main goal of collecting user input is to get a data that could be framed as packets in the end
// like modifiers state, keycode, pressed/released state. Then we can say 'user input was ...' interpet
// it like a command and send this command.
bool recorder_handle_record(uint16_t keycode, keyrecord_t *keyrecord){
    if (record_length >= RECORDER_MAX_KEYS){
        recorder_stop();
        return false;
    };

    record_buffer[record_length].keycode = keycode;
    record_buffer[record_length].active_mods = get_mods();
    record_buffer[record_length].pressed = keyrecord->event.pressed;

    record_length++;
    return false;
};

void recorder_process_buffer(recorder_entry_t *buffer, uint8_t length){
    // TODO: logic events to text. a-Z 0-9 ! @ # $ % ^ & * - _ + =

    for (uint8_t i = 0; i < length; i++) {
        uprintf(
            ">>> [%u] mods=%u key=%u pressed=%u\n",
            i,
            buffer[i].active_mods,
            buffer[i].keycode,
            buffer[i].pressed
        );

    }

};

