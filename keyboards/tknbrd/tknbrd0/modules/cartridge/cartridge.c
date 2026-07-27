#include "cartridge.h"
#include "debug.h"
#include "tknbrd0/custom_keycodes.h"
#include "tknbrd/tknbrd0/modules/event_queue/event_queue.h"
#include "tknbrd/tknbrd0/modules/transport/transport_uart.h"
#include "tknbrd/tknbrd0/modules/protocol/protocol.h"


#include "send_string.h"
#include "print.h"


// main initialisation of cartridge when inserted
void cartridge_init(){
    event_queue_init();
    transport_init();
    protocol_request_init();
};

//expecting some layer of tasks, so we can decorate some happenings with animation, etc...
void cartridge_task(void) {

    cartridge_event_t evt;
    transport_task();
    protocol_task();

    if (event_queue_pop(&evt)){
        switch (evt)
        {
            case EVENT_HELLO_HOST:
                send_string("HELLO HOST");
                break;
            case EVENT_CARTRIDGE_PING_PONG:
                protocol_request_ping();
                break;

            default:
                break;
        }
    }
};

bool user_input(uint16_t keycode, keyrecord_t *record){
    // if we caught keycode that meant to be handled as initiator of some happening in context of cartridge
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case HELLO:
            event_queue_push(EVENT_HELLO_HOST);
            return false;
            break;
        case PING_C:
            event_queue_push(EVENT_CARTRIDGE_PING_PONG);
            return false;
            break;
        default:
            //dprintf("NO MATCHING INPUT RECORDS WAS FOUND!");
            return true;
            break;

    }
    return true;
};
