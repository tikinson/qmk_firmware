#include "cartridge.h"
#include "debug.h"
#include "tknbrd0/custom_keycodes.h"
#include "tknbrd0/modules/event_queue/event_queue.h"
#include "send_string.h"
#include "print.h"



//main initialisation of cartridge when inserted
void cartridge_init(){
    event_queue_init();
};

//expecting some layer of tasks, so we can decorate some happenings with animation, etc...
void cartridge_task(void) {

    cartridge_event_t evt;

    while (event_queue_pop(&evt)){
        switch (evt)
        {
            case EVENT_HELLO_HOST:
                send_string("hello host!");
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
            dprintf("evt=%d\n", keycode);
            return false;
    }
    return true;
};
