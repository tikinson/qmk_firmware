#include "event_queue.h"
#include <stdint.h>
#include <strings.h>
#include "debug.h"
#include "ch.h"
#include "send_string.h"
#include "print.h"

static event_queue_t queue;

void event_queue_init(void) {
    queue.head = 0;
    queue.tail = 0;
};

bool event_queue_push(cartridge_event_t evt){

    // dprintf("%d PUSH is pushing event :\n", evt);
    uint8_t next = (queue.head + 1) % EVENT_QUEUE_SIZE;
    if (next == queue.tail){
        return false;
    }
    queue.data[queue.head] = evt;
    queue.head = next;

    return true;
};

bool event_queue_pop(cartridge_event_t *evt){
    if (queue.tail == queue.head){
        return false;
    }
    *evt = queue.data[queue.tail];
    queue.tail = (queue.tail + 1) % EVENT_QUEUE_SIZE;

    return true;
}
