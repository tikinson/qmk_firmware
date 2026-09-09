#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"

typedef struct {
    uint16_t keycode;
    bool pressed;
    uint8_t active_mods;
} recorder_entry_t;

void recorder_start(void);
void recorder_stop(void);
bool recorder_handle_record(uint16_t keycode, keyrecord_t *keyrecord);
void recorder_process_buffer(recorder_entry_t *record_buffer, uint8_t length);
