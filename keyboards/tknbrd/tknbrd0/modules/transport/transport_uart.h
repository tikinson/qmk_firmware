
#include <stdbool.h>
#include <stdint.h>

void transport_init(void);
void transport_send_packet(uint8_t *data, uint16_t len);
bool transport_receive_packet(uint8_t *data, uint16_t len);
void transport_task(void);
void transport_echo_packet(void);
