#include <stdint.h>
typedef enum {
    PROTOCOL_IDLE,
    PROTOCOL_WAITING_PONG,
    PROTOCOL_CONNECTED,
    PROTOCOL_DISCONNECTED,
} protocol_state_t;

typedef struct{
    uint8_t start;
    uint8_t type;
    uint8_t length;
    uint8_t payload[12];
    uint8_t stop;
} packet_t;

protocol_state_t protocol_get_state(void);
void protocol_request_ping(void);
void protocol_request_init(void);
void protocol_task(void);
void protocol_dispatch_incoming(const uint8_t *raw, uint16_t length);
