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

#define IS_S0 S.id.b00
#define IS_S1 S.id.b01
#define IS_S2 S.id.b02
#define IS_S3 S.id.b03
#define IS_S4 S.id.b04
#define IS_S5 S.id.b05
#define IS_S6 S.id.b06
#define IS_S7 S.id.b07
#define IS_S8 S.id.b08
#define IS_S9 S.id.b09
#define IS_S10 S.id.b10
/*
#define IS_A0 A.bits.b0
#define IS_A1 A.bits.b1
#define IS_A2 A.bits.b2
#define IS_A3 A.bits.b3
#define IS_A4 A.bits.b4
#define IS_A5 A.bits.b5
#define IS_A6 A.bits.b6
#define IS_A7 A.bits.b7
*/
#define TURN_ON_A0 TXREG=20;
#define TURN_ON_A1 TXREG=21;
#define TURN_ON_A2 TXREG=22;
#define TURN_ON_A3 TXREG=23;
#define TURN_ON_A4 TXREG=24;
#define TURN_ON_A5 TXREG=25;
#define TURN_ON_A6 TXREG=26;
#define TURN_ON_A7 TXREG=27;

#define TURN_OFF_A0 TXREG=0;
#define TURN_OFF_A1 TXREG=1;
#define TURN_OFF_A2 TXREG=2;
#define TURN_OFF_A3 TXREG=3;
#define TURN_OFF_A4 TXREG=4;
#define TURN_OFF_A5 TXREG=5;
#define TURN_OFF_A6 TXREG=6;
#define TURN_OFF_A7 TXREG=7;

sensors S;
bybit A;
unsigned char events_n_todo[10];
unsigned char events_n_todo_count;

// MEMORY BANK 0 (8bits)
// 0-1 = input_pallet
// 2-7 = elevator
#define bINPUT_PALLET_ACTIVE membank0.bits.b0
#define bINPUT_PALLET_S10 membank0.bits.b1
#define bMOVE_0_ACTIVE membank0.bits.b2
#define bELEVATOR_P0 membank0.bits.b3
#define bELEVATOR_P1 membank0.bits.b4
#define bELEVATOR_P2 membank0.bits.b5
#define bELEVATOR_P3 membank0.bits.b6
#define bMOVE_1_ACTIVE membank0.bits.b7
bybit membank0;

// MEMORY BANK 1 (8bits)
// 0-1 = elevator
// 2 = fit_box
// 3 = release_box
// 4-5 = floor
#define bMOVE_2_ACTIVE membank1.bits.b0
#define bMOVE_3_ACTIVE membank1.bits.b1
#define bFIT_BOX_ACTIVE membank1.bits.b2
#define bRELEASE_BOX_ACTIVE membank1.bits.b3
#define bOPEN_FLOOR_ACTIVE membank1.bits.b4
#define bCLOSE_FLOOR_ACTIVE membank1.bits.b5
bybit membank1;
bybit membank2;
bybit tmembank;

/************* INPUT_PALLET SEQUENCE OPERATIONS *************/
/*
 * INPUT_PALLET COMMANDS
 */
#define TURN_ON_INPUT_PALLET TURN_ON_A7
#define TURN_OFF_INPUT_PALLET TURN_OFF_A7

void input_pallet(void) {
	if (!bINPUT_PALLET_ACTIVE) {
		TURN_ON_INPUT_PALLET;
		bINPUT_PALLET_ACTIVE = 1;
		bINPUT_PALLET_S10 = IS_S10;
	}
}

void update_input_pallet(void) {
	if (bINPUT_PALLET_ACTIVE) {
		tmembank.bits.b0 = IS_S10;
		if (bINPUT_PALLET_S10) {
			bINPUT_PALLET_S10 = tmembank.bits.b0;
		} else {
			if (tmembank.bits.b0) {
				// end_input_pallet
				bINPUT_PALLET_ACTIVE = 0;
				TURN_OFF_INPUT_PALLET;
			}
		}
	}
}

/************* ELEVATOR SEQUENCE OPERATIONS *************/
/*
 * ELEVATOR COMMANDS
 */
#define ELEVATOR_UP TURN_ON_A5
#define ELEVATOR_UP_STOP TURN_OFF_A5
#define ELEVATOR_DOWN TURN_ON_A6
#define ELEVATOR_DOWN_STOP TURN_OFF_A6
#define ELEVATOR_IS_P0 IS_S6
#define ELEVATOR_IS_P1 IS_S9
#define ELEVATOR_IS_P2 IS_S8
#define ELEVATOR_IS_P3 IS_S7

void move_0(void) {
	if (!bMOVE_0_ACTIVE) {
		ELEVATOR_DOWN;
		bMOVE_0_ACTIVE = 1;
	}
}

void update_move_0(void) {
	if (bMOVE_0_ACTIVE) {
		if (ELEVATOR_IS_P0) {
			// end_move_0
			ELEVATOR_DOWN_STOP;
			bMOVE_0_ACTIVE = 0;
			bELEVATOR_P0 = 1;
			bELEVATOR_P1 = 0;
			bELEVATOR_P2 = 0;
			bELEVATOR_P3 = 0;
		}
	}
}

void move_1(void) {
	if (!bMOVE_1_ACTIVE) {
		if (bELEVATOR_P0) {
			ELEVATOR_UP;
		} else {
			ELEVATOR_DOWN;
		}
		bMOVE_1_ACTIVE = 1;
	}
}

void update_move_1(void) {
	if (bMOVE_1_ACTIVE) {
		if (ELEVATOR_IS_P1) {
			// end_move_1
			if (bELEVATOR_P0) {
				ELEVATOR_UP_STOP;
				bELEVATOR_P0 = 0;
			} else {
				ELEVATOR_DOWN_STOP;
				bELEVATOR_P2 = 0;
				bELEVATOR_P3 = 0;
			}
			bELEVATOR_P1 = 1;
			bMOVE_1_ACTIVE = 0;
		}
	}
}

void move_2(void) {
	if (!bMOVE_2_ACTIVE) {
		if (bELEVATOR_P0
			|| bELEVATOR_P1) {
			ELEVATOR_UP;
		} else {
			ELEVATOR_DOWN;
		}
		bMOVE_2_ACTIVE = 1;
	}
}

void update_move_2(void) {
	if (bMOVE_2_ACTIVE) {
		if (ELEVATOR_IS_P2) {
			// end_move_2
			if (bELEVATOR_P0
				|| bELEVATOR_P1) {
				ELEVATOR_UP_STOP;
				bELEVATOR_P0 = 0;
				bELEVATOR_P1 = 0;
			} else {
				ELEVATOR_DOWN_STOP;
				bELEVATOR_P3 = 0;
			}
			bELEVATOR_P2 = 1;
			bMOVE_2_ACTIVE = 0;
		}
	}
}

void move_3(void) {
	if (!bMOVE_3_ACTIVE) {
		ELEVATOR_UP;
		bMOVE_3_ACTIVE = 1;
	}
}

void update_move_3(void) {
	if (bMOVE_3_ACTIVE) {
		if (ELEVATOR_IS_P3) {
			// end_move_3
			ELEVATOR_UP_STOP;
			bELEVATOR_P0 = 0;
			bELEVATOR_P1 = 0;
			bELEVATOR_P2 = 0;
			bELEVATOR_P3 = 1;
			bMOVE_3_ACTIVE = 0;
		}
	}
}

/************* FIT_BOX SEQUENCE OPERATIONS *************/
/*
 * FIT_BOX/RELEASE_BOX COMMANDS
 */
#define FIT_BOX TURN_ON_A4
#define RELEASE_BOX TURN_OFF_A4
#define IS_BOX_FITTED IS_S5
#define IS_BOX_RELEASE !IS_S5

void fit_box(void) {
	if (!bFIT_BOX_ACTIVE) {
		FIT_BOX;
		bFIT_BOX_ACTIVE = 1;
	}
}

void update_fit_box(void) {
	if (bFIT_BOX_ACTIVE) {
		if (IS_BOX_FITTED) {
			// end_fit_box
			bFIT_BOX_ACTIVE = 0;
		}
	}
}

void release_box(void) {
	if (!bRELEASE_BOX_ACTIVE) {
		RELEASE_BOX;
		bRELEASE_BOX_ACTIVE = 1;
	}
}

void update_release_box(void) {
	if (bRELEASE_BOX_ACTIVE) {
		if (IS_BOX_RELEASE) {
			// end_release_box
			bRELEASE_BOX_ACTIVE = 0;
		}
	}
}

/************* FLOOR SEQUENCE OPERATIONS *************/
/*
 * FLOOR COMMANDS
 */
#define OPEN_FLOOR TURN_ON_A3
#define CLOSE_FLOOR TURN_OFF_A3
#define IS_FLOOR_OPENED IS_S3
#define IS_FLOOR_CLOSED IS_S4

void open_floor(void) {
	if (!bOPEN_FLOOR_ACTIVE) {
		bOPEN_FLOOR_ACTIVE = 1;
		OPEN_FLOOR;
	}
}

void update_open_floor(void) {
	if (bOPEN_FLOOR_ACTIVE) {
		if (IS_FLOOR_OPENED) {
			// end_open_floor
			bOPEN_FLOOR_ACTIVE = 0;
		}
	}
}

void close_floor(void) {
	if (!bCLOSE_FLOOR_ACTIVE) {
		bCLOSE_FLOOR_ACTIVE = 1;
		CLOSE_FLOOR;
	}
}

void update_close_floor(void) {
	if (bCLOSE_FLOOR_ACTIVE) {
		if (IS_FLOOR_CLOSED) {
			// end_close_floor
			bCLOSE_FLOOR_ACTIVE = 0;
		}
	}
}

/************************/
/***** INTERRUPT ********/
unsigned char seconds;
unsigned int tick;
void interrupt ISR_interrupt() {
    if (RCIF) { // test the interrupt for uart rx
        unsigned char c = RCREG;
        events_n_todo[events_n_todo_count++] = c;
        CREN = 0;
        CREN = 1;
    }
    if (TMR0IF) {
        tick += 16*2;
	if (tick >= 62500) {
		seconds++;
		tick -= 62500;
	}
        TMR0IE = 1;
        TMR0IF = 0;
        TMR0 = 0;
    }
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
    tick = 0;
    seconds = 0;
    
    // setup interrupts for Async USART
    IPEN=1; // enable priority //(mid-range compatibility)
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

    // setup TIMER0 interrupt
    TMR0IE = 1; //TMR0 Overflow Interrupt Enable bit
    TMR0IP = 1; // : TMR0 Overflow Interrupt Priority bit, 1 == High
    TMR0IF = 1; //: TMR0 Overflow Interrupt Flag bit
    TMR0ON = 1; //Timer0 On/Off Control bit
    T08BIT = 1; //: Timer0 8-bit/16-bit Control bit
    
    mylcd_init();

    S.bytes.byte1 = 0;
    S.bytes.byte2 = 0;
    A.byte = 0;

    unsigned char lcd_refresh_rate = 255;

    while (1) {
        lcd_refresh_rate--;
        if (lcd_refresh_rate == 0) {
            lcd_update(S, A);
            lcd_refresh_rate = 255;
        }
    }
}