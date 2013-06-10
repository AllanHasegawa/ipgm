#include "serial.h"

#define USE_OR_MASKS
#include <p18f452.h>
#include <usart.h>

void serial_init() {
    //-------------------------configure USART ---------------------------------------------------------
    // API configures USART for desired parameters:
    //  - TX/RX interrupts turned off
    //  - Asynchronous mode
    //  - 8 bits
    //  - Continuous Receive Enabled
    //  - Low speed baud rate generator mode (Fosc / 16)
    OpenUSART(USART_TX_INT_OFF | USART_RX_INT_OFF | USART_ASYNCH_MODE | USART_EIGHT_BIT | USART_CONT_RX | USART_BRGH_LOW, BAUD_RATE_GEN);
    //baudUSART(BAUD_8_BIT_RATE | BAUD_AUTO_OFF);
    //baudUSART(0b11110111 | 0b11111110);
}

void serial_send(unsigned char c) {
    putcUSART(c);
}

unsigned char serial_rcv() {
    return getcUSART();
    /*getsUSART((char *)Rxdata, 24);         // receive data up to 24 bytes
    Rxdata[24] = 0;                         // NULL terminate the string for putsUSART call.
    putsUSART((char *)Rxdata);*/
}

void serial_close() {
    CloseUSART();
}
