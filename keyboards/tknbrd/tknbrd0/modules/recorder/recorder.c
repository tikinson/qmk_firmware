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
bool recorder_collect(uint16_t keycode, keyrecord_t *keyrecord){
    if (record_length >= RECORDER_MAX_KEYS){
        recorder_stop();
        return false;
    };

    record_buffer[record_length].keycode = keycode;
    record_buffer[record_length].pressed = keyrecord->event.pressed;

    uprintf("[REC_COLLECT]: keycode=%u pressed=%u layer_state=0x%08lX\n",
        (unsigned int)keycode,
        keyrecord->event.pressed,
        (unsigned long)layer_state
    );

    record_length++;
    return false;
};

void recorder_process_buffer(recorder_entry_t *buffer, uint8_t length){
    // contract between captured events and string that meant to be sent

    for (uint8_t i = 0; i < length; i++) {

        uint16_t keycode = buffer[i].keycode;

        if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
            uint8_t mods = QK_MODS_GET_MODS(keycode);
            uint8_t basic = QK_MODS_GET_BASIC_KEYCODE(keycode);

            uprintf(
                "[REC] QK_MODS mods=0x%02X basic=0x%02X\n",
                mods,
                basic
            );
        }
        // else if (keycode >= KC_A && keycode <= KC_Z) {
        //     uprintf("[REC] LETTER keycode=0x%02X\n", keycode);
        // } else if (keycode <= QK_BASIC_MAX) {
        //     uprintf("[REC] BASIC keycode=0x%02X\n", keycode);
        // } else {
        //     uprintf("[REC] EXTENDED keycode=0x%04X\n", keycode);
        // }

    }
};

