#include <stdint.h>
#include <stdbool.h>

// typedef enum {
//     REC_START,
//     REC_STOP,
// } recorder_state_t;

void recorder_start(void);
void recorder_stop(void);
bool recorder_handle_record(uint16_t keycode);
