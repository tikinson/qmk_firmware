
#include "transport_uart.h"
#include <stdint.h>
#include "uart.h"
#include "string.h"

enum rx_state {
    RX_WAIT_START,
    RX_READ_TYPE,
    RX_READ_LENGTH,
    RX_READ_DATA
};

static enum rx_state rx_state = RX_WAIT_START;
static packet_t rx_packet;
static uint8_t rx_index;

// for now im not expecting long and complicated packet chains and protocols, just thinking about some
// small transmissions from keeb to cartridge, about 16 bytes per packet?

void transport_init(){
    uart_init(115200);
};

void transport_send_packet(uint8_t *data, uint16_t len){
    uart_transmit(data, len);
};

void transport_rx(){
    packet_t packet;
    if (uart_available()) {
        dprintf("packet=%d\n", packet);
    }
};
