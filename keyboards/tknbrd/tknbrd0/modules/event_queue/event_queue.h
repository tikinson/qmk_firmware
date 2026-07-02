#include "tknbrd/tknbrd0/modules/cartridge/cartridge.h"
#define EVENT_QUEUE_SIZE 8

typedef struct {
    cartridge_event_t data[EVENT_QUEUE_SIZE];
    uint8_t head;
    uint8_t tail;
} event_queue_t;

void event_queue_init(void);

bool event_queue_push(cartridge_event_t evt);
bool event_queue_pop(cartridge_event_t *evt);
