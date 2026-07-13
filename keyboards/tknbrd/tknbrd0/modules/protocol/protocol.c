#include "protocol.h"
#include <stdint.h>
#include "tknbrd0/modules/transport/transport_uart.h"

static enum protocol_state state;

void protocol_init_state(void){
    state = PROTOCOL_IDLE;
};

void protocol_ping(){
    uint8_t ping_packet[16] = {
        0xAA,
        0x01,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x88,
    };
    transport_send_packet(ping_packet, sizeof(ping_packet));
    state = PROTOCOL_WAITING_PONG;
};
