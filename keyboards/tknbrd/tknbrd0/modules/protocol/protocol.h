#include <stdint.h>
enum protocol_state {
    PROTOCOL_IDLE,
    PROTOCOL_WAITING_PONG,
    PROTOCOL_CONNECTED,
    PROTOCOL_DISCONNECTED,
};

typedef struct{
    uint8_t type;
    uint8_t length;
    uint8_t data[13];
    uint8_t end;
} packet_t;

void protocol_ping(void);
void protocol_init(void);
