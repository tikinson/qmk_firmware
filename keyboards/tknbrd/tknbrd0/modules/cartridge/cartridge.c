#include "cartridge.h"
#include "tknbrd0/custom_keycodes.h"
#include "ch.h"
#include "send_string.h"

static cartridge_event_t pending_evt = EVENT_NONE;

//main initialisation of cartridge when inserted
void cartridge_init(){

};

//expecting some layer of tasks, so we can decorate some happenings with animation, etc...
void cartridge_task(void) {

    if (pending_evt == EVENT_NONE)
        return;

    switch (pending_evt) {
        case EVENT_HELLO_HOST:

            //implement transport layer
            // cartridge_transport_send("hello\n");
            send_string("hello from cartridge side");
            break;

            default:
            break;
    }
    pending_evt = EVENT_NONE;
};

void cartridge_emit(cartridge_event_t evt){
    pending_evt = evt;
};

bool cartridge_input(uint16_t keycode, keyrecord_t *record){

        if (!record->event.pressed) {
            return true;
        }

        switch (keycode) {
            case HELLO:
                cartridge_emit(EVENT_HELLO_HOST);
                send_string("after emitting hello host");
                return false;
        }
        return true;
}
