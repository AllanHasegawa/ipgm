/* 
 * File:   main.c
 * Author: AranHase
 *
 * Created on June 9, 2013, 8:34 PM
 */
#include <p18f452.h>
#include "serial.h"
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

void main(void) {

    ADCON1 = 0x06;
    TRISA = 0xFF;
    TRISB = 0x00;
    TRISC = 0x01;
    TRISD = 0x00;
    TRISE = 0x00;

    serial_init();
    mylcd_init();

    S.bytes.byte1 = 255;
    S.bytes.byte2 = 0;
    A.byte = 5;

    unsigned char lcd_refresh_rate = 255;

    while (1) {
        unsigned char c = serial_rcv();

        if (c > 0) {
            serial_send(c);
        }
        lcd_refresh_rate--;
        if (lcd_refresh_rate == 0) {
            lcd_update(S, A);
            lcd_refresh_rate = 255;
        }
    }
}