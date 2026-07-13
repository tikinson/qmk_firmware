
#include "transport_uart.h"
#include <stdint.h>
#include "ch.h"
#include "debug.h"
#include "quantum.h"
#include "uart.h"
#include "string.h"

enum rx_state {
    RX_WAIT_START,
    RX_READ_TYPE,
    RX_READ_LENGTH,
    RX_READ_DATA
};

static enum rx_state rx_state = RX_WAIT_START;
// static packet_t rx_packet;
// static uint8_t rx_index;

// for now im not expecting long and complicated packet chains and protocols, just thinking about some
// small transmissions from keeb to cartridge, about 16 bytes per packet?

void transport_init(){
    uart_init(115200);
};

void transport_send_packet(uint8_t *data, uint16_t len){
    uart_transmit(data, len);
};

void transport_task(){
    uint8_t buffer[16];

    if(transport_receive_packet(buffer, 16))
    {
        dprintf("got packet\n");
    }
};

bool transport_receive_packet(uint8_t *data, uint16_t len){
    uint16_t available = uart_available();

    if (available < len)
    {
        return false;
    }
    dprintf("uart bytes: %d\n", available);
    rx_state = RX_READ_DATA;
    uart_receive(data, len);
    rx_state = RX_WAIT_START;
    dprintf("packet received\n");

    return true;
};

void transport_echo_byte(void){
    if (uart_available()){
        uint8_t data;
        uart_receive(&data, 1);
        uart_write(data);
    }
};
