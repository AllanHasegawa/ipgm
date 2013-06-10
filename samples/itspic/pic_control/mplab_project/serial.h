/* 
 * File:   serial.h
 * Author: AranHase
 *
 * Created on June 9, 2013, 8:58 PM
 */

#ifndef SERIAL_H
#define	SERIAL_H

// BAUD_RATE_GEN is calculated as  = [Fosc / (64 * Desired Baudrate)] - 1
// It needs to be changed depending upon oscillator frequency.
//  8MHz / (64 * 2400) - 1 = 51 (approx.)
#define BAUD_RATE_GEN 51                    // Fosc = 8MHz, Baud Rate = 2400 bps

void serial_init();
void serial_send(unsigned char c);
unsigned char serial_rcv();
void serial_close();

#endif	/* SERIAL_H */

