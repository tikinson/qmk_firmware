#include "protocol.h"
#include <stdint.h>
#include "string.h"
#include "tknbrd0/modules/transport/transport_uart.h"

static protocol_state_t state;

typedef enum {
    PKT_PING = 0x01,
    PKT_PONG = 0x02,
    PKT_INIT = 0xAD,
}packet_type_t;

protocol_state_t protocol_get_state(){
    return state;
};

void protocol_request_init(void){
    state = PROTOCOL_IDLE;

    packet_t packet = {
        .start = 0xAA,
        .type = PKT_INIT,
        .length = 3,
        .payload = {0x12,0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00},
        .stop = 0x88,
    };

    transport_send_packet((uint8_t *)&packet, sizeof(packet));
};

void protocol_request_ping(void){

    packet_t packet = {
        .start = 0xAA,
        .type = PKT_PING,
        .length = 0,
        .payload = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00},
        .stop = 0x88,
    };

    transport_send_packet((uint8_t *)&packet, sizeof(packet));
    // waiting but need to be limited by timeout
    state = PROTOCOL_WAITING_PONG;

};

void protocol_task(){
    if (state == PROTOCOL_WAITING_PONG) {
        //for example blink indicator, write text on oled etc.
    }
};

//what kind of packet we're expecting to interpret now?
void protocol_dispatch_incoming(const uint8_t *raw, uint16_t length){
    if (length != sizeof(packet_t)){
        return;
    }
    const packet_t *pkt = (const packet_t *)raw;

    //raw data not packet like; maybe need handling in future
    if (pkt->start != 0xAA) return;

    switch (pkt->type) {

        // case PKT_INIT:
        //     //protocol_handle_init(pkt);
        //     break;

        case PKT_PONG:
            //FOR NOW it will be echo!!
            transport_send_packet((uint8_t *)pkt, sizeof(*pkt));
            state = PROTOCOL_IDLE;
            break;

        default:
            break;
    }
};


