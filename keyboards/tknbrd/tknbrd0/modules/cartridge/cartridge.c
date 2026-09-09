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
    //TODO: transport_init must be called when CARTRIDGE IS INSERTED, not manually here!

    //transport_init();
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
            case EVENT_UREC_START:
                hud_notify_by_area("REC", HUD_AREA_RECORD);
                recorder_start();
                state = STATE_RECORDING;
                break;
            case EVENT_UREC_STOP:
                hud_notify_by_area("   ", HUD_AREA_RECORD);
                recorder_stop();
                state = STATE_IDLE;
                break;

            default:
                state = STATE_IDLE;
                break;
        }
    }
};

bool user_input(uint16_t keycode, keyrecord_t *record){
    // is keycode action or useful info in context of cartridge?

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

    };

    if (state == STATE_RECORDING) {
        recorder_handle_record(keycode, record);
        //return false;
    };

    return true;
};
