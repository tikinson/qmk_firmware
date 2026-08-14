#include <stdint.h>

typedef enum {
    REC_START,
    REC_STOP,
} recorder_state_t;

void recorder_start(void);
void recorder_stop(void);
void recorder_handle_record(uint16_t keycode);
