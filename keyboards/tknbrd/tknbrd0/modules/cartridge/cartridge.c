#include "cartridge.h"
#include "debug.h"
#include "tknbrd0/custom_keycodes.h"
#include "tknbrd/tknbrd0/modules/event_queue/event_queue.h"
#include "tknbrd/tknbrd0/modules/transport/transport_uart.h"
#include "tknbrd/tknbrd0/modules/protocol/protocol.h"
#include "tknbrd/tknbrd0/modules/hud/hud.h"
#include "tknbrd/tknbrd0/modules/recorder/recorder.h"


#include "send_string.h"
#include "print.h"

static cartridge_state_t state;

// main initialisation of cartridge when inserted
void cartridge_init(void){
    event_queue_init();
    transport_init();
    state = STATE_IDLE;
    //protocol_request_init();

};

cartridge_state_t cartridge_get_state(){
    return state;
};

//expecting some layer of tasks, so we can decorate some happenings with animation, etc...
void cartridge_task(void) {

    cartridge_event_t evt;
    transport_task();
    //protocol_task();

    if (event_queue_pop(&evt)){
        switch (evt){

            case EVENT_HELLO_HOST:
                //send_string("HELLO HOST");
                protocol_send_debug("event hello");
                break;
            case EVENT_CARTRIDGE_PING_PONG:
                protocol_request_ping();
                break;

            //rec_start rec_stop events here only for user notifying for now,
            //rest of the user input capturing probably will be not here.

            case EVENT_UREC_START:
                //hud_notify_by_area("REC", HUD_AREA_RECORD);
                state = STATE_RECORDING;
                recorder_start();
                break;
            case EVENT_UREC_STOP:
                //hud_notify_by_area("   ", HUD_AREA_RECORD);
                state = STATE_RECORDED;
                recorder_stop();
                break;

            default:
                state = STATE_IDLE;
                break;
        }
    }
};

bool user_input(uint16_t keycode, keyrecord_t *record){
    // if we caught keycode that meant to be handled as initiator of some happening in context of cartridge
    if (!record->event.pressed) {
        return true;
    };

    if (state == STATE_RECORDING) {
        recorder_handle_record(keycode);
        return true;
    };

    switch (keycode) {
        case HELLO:
            event_queue_push(EVENT_HELLO_HOST);
            return false;
            break;
        case PING_C:
            event_queue_push(EVENT_CARTRIDGE_PING_PONG);
            return false;
            break;
        case UREC_START:
            event_queue_push(EVENT_UREC_START);
            return false;
            break;
        case UREC_STOP:
            event_queue_push(EVENT_UREC_STOP);
            return false;
            break;
        default:
            //dprintf("NO MATCHING INPUT RECORDS WAS FOUND!");
            return true;
            break;

    }
    return true;
};
