#pragma once

#include <stdint.h>
#include "quantum.h"

typedef enum {
    EVENT_NONE,
    EVENT_HELLO_HOST,
    EVENT_CARTRIDGE_PING_PONG,
    EVENT_ECHO_BYTE,
    EVENT_UREC_START,
    EVENT_UREC_STOP,
} cartridge_event_t;

typedef enum {
    STATE_RECORDING,
    STATE_RECORDED,
    STATE_IDLE,
} cartridge_state_t;

cartridge_state_t cartridge_get_state(void);

void cartridge_init(void);
void cartridge_task(void);

bool user_input(uint16_t keycode, keyrecord_t *record);
