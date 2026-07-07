
#include "transport_uart.h"
#include <stdint.h>
#include "uart.h"
#include "string.h"

void transport_init(){
    uart_init(115200);
};

void transport_send_ping(){
    // uint8_t packet[3];
    // packet[0] = 0xAA;
    // packet[1] = 0x01;
    // packet[2] = 0x00;
    // uart_transmit(packet, 3);

    // const char *msg = "UART IS WORKING\r\n";
    // uart_transmit((const uint8_t *)msg, strlen(msg));

    uart_write(0xAA);

};
