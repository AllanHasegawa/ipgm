/* 
 * File:   main.c
 * Author: AranHase
 *
 * Created on June 9, 2013, 8:34 PM
 */
#include <p18f452.h>
#include "atraso.h"
#include "mylcd.h"
#include "datatypes.h"

#pragma config WDT=OFF

//#pragma config WDT=OFF,CP0=ON,OSCS=ON,OSC=LP,BOR=ON,BORV=25,WDTPS=128,CCP2MUX=ON
//#pragma config OSCS=ON
//#pragma config OSC=LP

#define SetBit(v,bit) v |= (1 << bit);
#define ClearBit(v,bit) v &= ~(1 << bit);
#define IsBit(v,bit) ((v & (1 << bit)) >> bit)

sensors S;
bybit A;

unsigned char events_n_todo[10];
unsigned char events_n_todo_count;

void interrupt ISR_interrupt() {
    if (RCIF) { // test the interrupt for uart rx
        unsigned char c = RCREG;
        events_n_todo[events_n_todo_count++] = c;
        S.bytes.byte1 = c;
        S.bytes.byte2 = 0;
    }
    CREN = 0;
    CREN = 1;
    GIEH = 1;
}

void main(void) {

    ADCON1 = 0x06;
    TRISA = 0xFF;
    TRISB = 0x00;
    //TRISC = 0x01;
    TRISD = 0x00;
    TRISE = 0x00;

    events_n_todo_count = 0;
    
    // setup interrupts for Async USART
    IPEN=1; // disable priority (mid-range compatibility)
    GIEH=1; // enables all interrupts that have the priority bit set
    GIEL=1; // enables all interrupts that have the priority bit cleared
    PEIE=1; // enables/disables all peripheral interrupt sources

    // setup Async USART for receive
    RCIE = 1;
    SPEN = 1;
    TRISC = 0;
    SetBit(TRISC,7);
    TXSTA = 0;
    SYNC = 0; // async mode
    BRGH = 1; // high/low speed
    CREN = 1; // enable receiver (async)

    // setup the rest of USART for async tx
    TXIE = 0; // no need for interrupt ;)
    TXEN = 1; // enable tx bit

    mylcd_init();

    S.bytes.byte1 = 10;
    S.bytes.byte2 = 0;
    A.byte = 5;

    unsigned char lcd_refresh_rate = 255;

    while (1) {
        lcd_refresh_rate--;
        if (lcd_refresh_rate == 0) {
            lcd_update(S, A);
            lcd_refresh_rate = 255;
        }
    }
}