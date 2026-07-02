#pragma once

#include <stdint.h>
#include "quantum.h"

typedef enum {
    EVENT_NONE,
    EVENT_HELLO_HOST,
} cartridge_event_t;

void cartridge_init(void);
void cartridge_task(void);

bool user_input(uint16_t keycode, keyrecord_t *record);
