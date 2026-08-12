
#include "transport_uart.h"
#include <stdint.h>
#include "_wait.h"
#include "ch.h"
#include "debug.h"
#include "quantum.h"
#include "uart.h"
#include "string.h"
#include "tknbrd/tknbrd0/modules/protocol/protocol.h"

#define PACKET_SIZE 16
#define BAUDRATE 115200

enum rx_state {
    RX_WAIT_START,
    RX_START,
    RX_COMPLETE
};

static enum rx_state rx_state = RX_WAIT_START;
// static packet_t rx_packet;
// static uint8_t rx_index;

// for now im not expecting long and complicated packet chains and protocols, just thinking about some
// small transmissions from keeb to cartridge, about 16 bytes per packet?

void transport_init(){
    uart_init(BAUDRATE);
    rx_state = RX_WAIT_START;
};

void transport_send_packet(uint8_t *data, uint16_t len){
    uart_transmit(data, len);
};

static    uint8_t rx_buffer[PACKET_SIZE];
//static    uint8_t rx_index;

void transport_task(){

    //let's deal with framing
    //check for bytes in uart fifo buffer
    if (!uart_available()){
        return;
    }
    rx_state = RX_START;
    uart_receive(rx_buffer, PACKET_SIZE);
    //is it actually packet received?
    protocol_dispatch_incoming(rx_buffer, PACKET_SIZE);
    rx_state = RX_COMPLETE;
};


