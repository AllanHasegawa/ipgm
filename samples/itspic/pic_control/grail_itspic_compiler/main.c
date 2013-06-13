#include <p18f452.h>
#include <stdlib.h>
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

#define IS_A0 A.bits.b0
#define IS_A1 A.bits.b1
#define IS_A2 A.bits.b2
#define IS_A3 A.bits.b3
#define IS_A4 A.bits.b4
#define IS_A5 A.bits.b5
#define IS_A6 A.bits.b6
#define IS_A7 A.bits.b7

#define TURN_ON_S0 S.id.b00=1;
#define TURN_ON_S1 S.id.b01=1;
#define TURN_ON_S2 S.id.b02=1;
#define TURN_ON_S3 S.id.b03=1;
#define TURN_ON_S4 S.id.b04=1;
#define TURN_ON_S5 S.id.b05=1;
#define TURN_ON_S6 S.id.b06=1;
#define TURN_ON_S7 S.id.b07=1;
#define TURN_ON_S8 S.id.b08=1;
#define TURN_ON_S9 S.id.b09=1;
#define TURN_ON_S10 S.id.b10=1;

#define TURN_OFF_S0 S.id.b00=0;
#define TURN_OFF_S1 S.id.b01=0;
#define TURN_OFF_S2 S.id.b02=0;
#define TURN_OFF_S3 S.id.b03=0;
#define TURN_OFF_S4 S.id.b04=0;
#define TURN_OFF_S5 S.id.b05=0;
#define TURN_OFF_S6 S.id.b06=0;
#define TURN_OFF_S7 S.id.b07=0;
#define TURN_OFF_S8 S.id.b08=0;
#define TURN_OFF_S9 S.id.b09=0;
#define TURN_OFF_S10 S.id.b10=0;

#define SERIAL_TX(n) while(!TXIF);TXREG=n;

#define TURN_OFF_A0 SERIAL_TX(30);A.bits.b0=0;
#define TURN_OFF_A1 SERIAL_TX(31);A.bits.b1=0;
#define TURN_OFF_A2 SERIAL_TX(32);A.bits.b2=0;
#define TURN_OFF_A3 SERIAL_TX(33);A.bits.b3=0;
#define TURN_OFF_A4 SERIAL_TX(34);A.bits.b4=0;
#define TURN_OFF_A5 SERIAL_TX(35);A.bits.b5=0;
#define TURN_OFF_A6 SERIAL_TX(36);A.bits.b6=0;
#define TURN_OFF_A7 SERIAL_TX(37);A.bits.b7=0;

#define TURN_ON_A0 SERIAL_TX(130);A.bits.b0=1;
#define TURN_ON_A1 SERIAL_TX(131);A.bits.b1=1;
#define TURN_ON_A2 SERIAL_TX(132);A.bits.b2=1;
#define TURN_ON_A3 SERIAL_TX(133);A.bits.b3=1;
#define TURN_ON_A4 SERIAL_TX(134);A.bits.b4=1;
#define TURN_ON_A5 SERIAL_TX(135);A.bits.b5=1;
#define TURN_ON_A6 SERIAL_TX(136);A.bits.b6=1;
#define TURN_ON_A7 SERIAL_TX(137);A.bits.b7=1;

#define RAISE_EVENT_N_END_MOVE_2 events_n_todo[events_n_todo_count++] = EVENT_N_END_MOVE_2;
#define RAISE_EVENT_N_END_MOVE_3 events_n_todo[events_n_todo_count++] = EVENT_N_END_MOVE_3;
#define RAISE_EVENT_N_END_MOVE_0 events_n_todo[events_n_todo_count++] = EVENT_N_END_MOVE_0;
#define RAISE_EVENT_N_END_MOVE_1 events_n_todo[events_n_todo_count++] = EVENT_N_END_MOVE_1;
#define RAISE_EVENT_N_END_OPEN_FLOOR events_n_todo[events_n_todo_count++] = EVENT_N_END_OPEN_FLOOR;
#define RAISE_EVENT_N_END_CLOSE_FLOOR events_n_todo[events_n_todo_count++] = EVENT_N_END_CLOSE_FLOOR;
#define RAISE_EVENT_N_END_FIT_BOX events_n_todo[events_n_todo_count++] = EVENT_N_END_FIT_BOX;
#define RAISE_EVENT_N_END_INPUT_BOX events_n_todo[events_n_todo_count++] = EVENT_N_END_INPUT_BOX;
#define RAISE_EVENT_N_END_RELEASE_BOX events_n_todo[events_n_todo_count++] = EVENT_N_END_RELEASE_BOX;
#define RAISE_EVENT_N_END_INPUT_PALLET events_n_todo[events_n_todo_count++] = EVENT_N_END_INPUT_PALLET;

#define EVENT_C_MOVE_0 0
#define EVENT_C_MOVE_1 1
#define EVENT_C_MOVE_2 2
#define EVENT_C_MOVE_3 3
#define EVENT_C_CLOSE_FLOOR 4
#define EVENT_C_INPUT_PALLET 5
#define EVENT_C_INPUT_BOX 6
#define EVENT_C_FIT_BOX 7
#define EVENT_C_OPEN_FLOOR 8
#define EVENT_C_RELEASE_BOX 9
#define EVENT_N_END_MOVE_2 10
#define EVENT_N_END_MOVE_3 11
#define EVENT_N_END_MOVE_0 12
#define EVENT_N_END_MOVE_1 13
#define EVENT_N_END_OPEN_FLOOR 14
#define EVENT_N_END_CLOSE_FLOOR 15
#define EVENT_N_END_FIT_BOX 16
#define EVENT_N_END_INPUT_BOX 17
#define EVENT_N_END_RELEASE_BOX 18
#define EVENT_N_END_INPUT_PALLET 19


#define DES_EVENT_MOVE_0 des0.bits.b0 = 1;
#define DES_EVENT_MOVE_1 des0.bits.b1 = 1;
#define DES_EVENT_MOVE_2 des0.bits.b2 = 1;
#define DES_EVENT_MOVE_3 des0.bits.b3 = 1;
#define DES_EVENT_CLOSE_FLOOR des0.bits.b4 = 1;
#define DES_EVENT_INPUT_PALLET des0.bits.b5 = 1;
#define DES_EVENT_INPUT_BOX des0.bits.b6 = 1;
#define DES_EVENT_FIT_BOX des0.bits.b7 = 1;
#define DES_EVENT_OPEN_FLOOR des1.bits.b0 = 1;
#define DES_EVENT_RELEASE_BOX des1.bits.b1 = 1;


#define IS_DES_EVENT_MOVE_0 (des0.bits.b0 == 1)
#define IS_DES_EVENT_MOVE_1 (des0.bits.b1 == 1)
#define IS_DES_EVENT_MOVE_2 (des0.bits.b2 == 1)
#define IS_DES_EVENT_MOVE_3 (des0.bits.b3 == 1)
#define IS_DES_EVENT_CLOSE_FLOOR (des0.bits.b4 == 1)
#define IS_DES_EVENT_INPUT_PALLET (des0.bits.b5 == 1)
#define IS_DES_EVENT_INPUT_BOX (des0.bits.b6 == 1)
#define IS_DES_EVENT_FIT_BOX (des0.bits.b7 == 1)
#define IS_DES_EVENT_OPEN_FLOOR (des1.bits.b0 == 1)
#define IS_DES_EVENT_RELEASE_BOX (des1.bits.b1 == 1)
// keep state of sensors and actuators
sensors S;
bybit A;

// keep a queue of events to be processed
unsigned char events_n_todo[10];
unsigned char events_n_todo_count;

// used with TMR0 through all operations
unsigned int seconds;

// keep supervisors state
unsigned char s0_s;
unsigned char s1_s;
unsigned char s2_s;
unsigned char s3_s;

// desabilitation variables
bybit des0;
bybit des1;



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
// 6-7 = input_box
#define bMOVE_2_ACTIVE membank1.bits.b0
#define bMOVE_3_ACTIVE membank1.bits.b1
#define bFIT_BOX_ACTIVE membank1.bits.b2
#define bRELEASE_BOX_ACTIVE membank1.bits.b3
#define bOPEN_FLOOR_ACTIVE membank1.bits.b4
#define bCLOSE_FLOOR_ACTIVE membank1.bits.b5
#define bINPUT_BOX_ACTIVE membank1.bits.b6
#define bINPUT_BOX_FIRST membank1.bits.b7
bybit membank1;

// MEMORY BANK 2 (8bits)
// 0 = input_box
#define bINPUT_BOX_SECOND membank2.bits.b0
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
                RAISE_EVENT_N_END_INPUT_PALLET;
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
            RAISE_EVENT_N_END_MOVE_0;
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
            RAISE_EVENT_N_END_MOVE_1;
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
            RAISE_EVENT_N_END_MOVE_2;
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
            RAISE_EVENT_N_END_MOVE_3;
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
            RAISE_EVENT_N_END_FIT_BOX;
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
            RAISE_EVENT_N_END_RELEASE_BOX;
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
            RAISE_EVENT_N_END_OPEN_FLOOR;
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
            RAISE_EVENT_N_END_CLOSE_FLOOR;
        }
    }
}

/************* INPUT_BOX SEQUENCE OPERATIONS *************/
/*
 * INPUT_BOX COMMANDS
 */
#define TURN_ON_UP_BOX TURN_ON_A0
#define TURN_OFF_UP_BOX TURN_OFF_A0
#define TURN_ON_PUSH_BOX TURN_ON_A1
#define TURN_OFF_PUSH_BOX TURN_OFF_A1

void input_box(void) {
    if (!bINPUT_BOX_ACTIVE) {
        TURN_ON_UP_BOX;
        bINPUT_BOX_ACTIVE = 1;
        bINPUT_BOX_FIRST = 0;
        bINPUT_BOX_SECOND = 0;
    }
}

unsigned int input_box_tmr;
void update_input_box(void) {
    if (bINPUT_BOX_ACTIVE) {
        if (bINPUT_BOX_SECOND) {
            if (IS_S2) {
                if (input_box_tmr > seconds) {
                    input_box_tmr = seconds;
                }
                if ((input_box_tmr + 10) < seconds) {
                    // end_input_box
                    bINPUT_BOX_ACTIVE = 0;
                    RAISE_EVENT_N_END_INPUT_BOX;
                }
            } else {
                input_box_tmr = seconds;
            }
        } else {
            if (IS_A1) {
                if (IS_S1) {
                    TURN_OFF_PUSH_BOX;
                    if (bINPUT_BOX_FIRST) {
                        input_box_tmr = seconds;
                        bINPUT_BOX_SECOND = 1;
                        TURN_OFF_UP_BOX;
                    } else {
                        bINPUT_BOX_FIRST = 1;
                    }
                }
            } else {
                if (IS_S0) {
                    TURN_ON_PUSH_BOX;
                }
            }
        }
    }
}

unsigned char events_n_todo[10];
unsigned char events_n_todo_count;

void sup_response_step() {
unsigned char i = 0;
for (; i < events_n_todo_count;i++) {
const unsigned char a_event = events_n_todo[i];
if (s0_s == 1) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 4;
	}
}
else if (s0_s == 2) {
	if (a_event == EVENT_N_END_MOVE_0) {
		s0_s = 7;
	}
}
else if (s0_s == 3) {
	if (a_event == EVENT_N_END_MOVE_3) {
		s0_s = 8;
	}
}
else if (s0_s == 5) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 9;
	}
	else if (a_event == EVENT_N_END_MOVE_0) {
		s0_s = 11;
	}
}
else if (s0_s == 6) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 10;
	}
	else if (a_event == EVENT_N_END_MOVE_3) {
		s0_s = 12;
	}
}
else if (s0_s == 9) {
	if (a_event == EVENT_N_END_MOVE_0) {
		s0_s = 13;
	}
}
else if (s0_s == 10) {
	if (a_event == EVENT_N_END_MOVE_3) {
		s0_s = 14;
	}
}
else if (s0_s == 11) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 13;
	}
}
else if (s0_s == 12) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 14;
	}
}
else if (s0_s == 15) {
	if (a_event == EVENT_N_END_RELEASE_BOX) {
		s0_s = 16;
	}
}
else if (s0_s == 17) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 19;
	}
}
else if (s0_s == 18) {
	if (a_event == EVENT_N_END_MOVE_2) {
		s0_s = 21;
	}
}
else if (s0_s == 20) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 22;
	}
	else if (a_event == EVENT_N_END_MOVE_2) {
		s0_s = 23;
	}
}
else if (s0_s == 22) {
	if (a_event == EVENT_N_END_MOVE_2) {
		s0_s = 24;
	}
}
else if (s0_s == 23) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 24;
	}
}
else if (s0_s == 25) {
	if (a_event == EVENT_N_END_RELEASE_BOX) {
		s0_s = 26;
	}
}
else if (s0_s == 27) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 29;
	}
}
else if (s0_s == 28) {
	if (a_event == EVENT_N_END_MOVE_1) {
		s0_s = 31;
	}
}
else if (s0_s == 30) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 32;
	}
	else if (a_event == EVENT_N_END_MOVE_1) {
		s0_s = 33;
	}
}
else if (s0_s == 32) {
	if (a_event == EVENT_N_END_MOVE_1) {
		s0_s = 34;
	}
}
else if (s0_s == 33) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 34;
	}
}
else if (s0_s == 35) {
	if (a_event == EVENT_N_END_RELEASE_BOX) {
		s0_s = 36;
	}
}
else if (s0_s == 37) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 39;
	}
}
else if (s0_s == 38) {
	if (a_event == EVENT_N_END_MOVE_0) {
		s0_s = 7;
	}
}
else if (s0_s == 40) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s0_s = 41;
	}
	else if (a_event == EVENT_N_END_MOVE_0) {
		s0_s = 11;
	}
}
else if (s0_s == 41) {
	if (a_event == EVENT_N_END_MOVE_0) {
		s0_s = 13;
	}
}
if (s1_s == 1) {
	if (a_event == EVENT_N_END_CLOSE_FLOOR) {
		s1_s = 2;
	}
}
else if (s1_s == 3) {
	if (a_event == EVENT_N_END_FIT_BOX) {
		s1_s = 4;
	}
}
else if (s1_s == 5) {
	if (a_event == EVENT_N_END_OPEN_FLOOR) {
		s1_s = 6;
	}
}
else if (s1_s == 7) {
	if (a_event == EVENT_N_END_RELEASE_BOX) {
		s1_s = 0;
	}
}
if (s2_s == 1) {
	if (a_event == EVENT_N_END_INPUT_BOX) {
		s2_s = 2;
	}
}
else if (s2_s == 3) {
	if (a_event == EVENT_N_END_CLOSE_FLOOR) {
		s2_s = 4;
	}
}
else if (s2_s == 5) {
	if (a_event == EVENT_N_END_INPUT_BOX) {
		s2_s = 7;
	}
}
else if (s2_s == 6) {
	if (a_event == EVENT_N_END_OPEN_FLOOR) {
		s2_s = 0;
	}
}
else if (s2_s == 8) {
	if (a_event == EVENT_N_END_INPUT_BOX) {
		s2_s = 9;
	}
	else if (a_event == EVENT_N_END_OPEN_FLOOR) {
		s2_s = 1;
	}
}
else if (s2_s == 9) {
	if (a_event == EVENT_N_END_OPEN_FLOOR) {
		s2_s = 2;
	}
}
if (s3_s == 1) {
	if (a_event == EVENT_N_END_MOVE_0) {
		s3_s = 4;
	}
}
else if (s3_s == 2) {
	if (a_event == EVENT_N_END_MOVE_1) {
		s3_s = 5;
	}
}
else if (s3_s == 3) {
	if (a_event == EVENT_N_END_MOVE_2) {
		s3_s = 6;
	}
}
else if (s3_s == 7) {
	if (a_event == EVENT_N_END_INPUT_PALLET) {
		s3_s = 8;
	}
}
else if (s3_s == 9) {
	if (a_event == EVENT_N_END_MOVE_3) {
		s3_s = 10;
	}
}
}
events_n_todo_count = 0;
}

void des_step(void) {
des0.byte = 0;
des1.byte = 0;
if (s0_s == 0) {
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 1) {
DES_EVENT_FIT_BOX;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 2) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 3) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 4) {
DES_EVENT_FIT_BOX;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 7) {
DES_EVENT_MOVE_0;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 8) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 11) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 13) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 14) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 16) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_1;
}
else if (s0_s == 17) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_1;
}
else if (s0_s == 18) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 19) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_1;
}
else if (s0_s == 21) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 24) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 26) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
}
else if (s0_s == 27) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
}
else if (s0_s == 28) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 29) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
}
else if (s0_s == 31) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 34) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 36) {
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 37) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 38) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
else if (s0_s == 39) {
DES_EVENT_FIT_BOX;
DES_EVENT_MOVE_3;
DES_EVENT_RELEASE_BOX;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_1;
}
if (s1_s == 0) {
DES_EVENT_FIT_BOX;
DES_EVENT_OPEN_FLOOR;
DES_EVENT_RELEASE_BOX;
}
else if (s1_s == 2) {
DES_EVENT_CLOSE_FLOOR;
DES_EVENT_OPEN_FLOOR;
DES_EVENT_RELEASE_BOX;
}
else if (s1_s == 4) {
DES_EVENT_CLOSE_FLOOR;
DES_EVENT_FIT_BOX;
DES_EVENT_RELEASE_BOX;
}
else if (s1_s == 6) {
DES_EVENT_CLOSE_FLOOR;
DES_EVENT_FIT_BOX;
DES_EVENT_OPEN_FLOOR;
}
if (s2_s == 0) {
DES_EVENT_CLOSE_FLOOR;
DES_EVENT_OPEN_FLOOR;
}
else if (s2_s == 2) {
DES_EVENT_INPUT_BOX;
DES_EVENT_OPEN_FLOOR;
}
else if (s2_s == 4) {
DES_EVENT_CLOSE_FLOOR;
}
else if (s2_s == 5) {
DES_EVENT_INPUT_BOX;
DES_EVENT_CLOSE_FLOOR;
}
else if (s2_s == 6) {
DES_EVENT_CLOSE_FLOOR;
DES_EVENT_OPEN_FLOOR;
}
else if (s2_s == 7) {
DES_EVENT_INPUT_BOX;
DES_EVENT_CLOSE_FLOOR;
}
if (s3_s == 0) {
DES_EVENT_INPUT_PALLET;
DES_EVENT_MOVE_3;
}
else if (s3_s == 4) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_1;
DES_EVENT_MOVE_2;
DES_EVENT_MOVE_3;
}
else if (s3_s == 5) {
DES_EVENT_MOVE_1;
DES_EVENT_INPUT_PALLET;
DES_EVENT_MOVE_3;
}
else if (s3_s == 6) {
DES_EVENT_MOVE_2;
DES_EVENT_INPUT_PALLET;
DES_EVENT_MOVE_3;
}
else if (s3_s == 8) {
DES_EVENT_MOVE_0;
DES_EVENT_MOVE_1;
DES_EVENT_MOVE_2;
DES_EVENT_INPUT_PALLET;
}
else if (s3_s == 10) {
DES_EVENT_INPUT_PALLET;
DES_EVENT_MOVE_3;
}
}

unsigned char decisions[10];
unsigned char decisions_count;
unsigned char decided_action;
void decisions_step() {
decisions_count = 0;
if (IS_DES_EVENT_MOVE_0) {
	decisions[decisions_count++] = EVENT_C_MOVE_0;
}
if (IS_DES_EVENT_MOVE_1) {
	decisions[decisions_count++] = EVENT_C_MOVE_1;
}
if (IS_DES_EVENT_MOVE_2) {
	decisions[decisions_count++] = EVENT_C_MOVE_2;
}
if (IS_DES_EVENT_MOVE_3) {
	decisions[decisions_count++] = EVENT_C_MOVE_3;
}
if (IS_DES_EVENT_CLOSE_FLOOR) {
	decisions[decisions_count++] = EVENT_C_CLOSE_FLOOR;
}
if (IS_DES_EVENT_INPUT_PALLET) {
	decisions[decisions_count++] = EVENT_C_INPUT_PALLET;
}
if (IS_DES_EVENT_INPUT_BOX) {
	decisions[decisions_count++] = EVENT_C_INPUT_BOX;
}
if (IS_DES_EVENT_FIT_BOX) {
	decisions[decisions_count++] = EVENT_C_FIT_BOX;
}
if (IS_DES_EVENT_OPEN_FLOOR) {
	decisions[decisions_count++] = EVENT_C_OPEN_FLOOR;
}
if (IS_DES_EVENT_RELEASE_BOX) {
	decisions[decisions_count++] = EVENT_C_RELEASE_BOX;
}
decided_action = rand() % decisions_count;
}

void sup_advance_step() {
if (decided_action == EVENT_C_MOVE_0) {
if (s0_s == 0) {
s0_s = 2;
}
else if (s0_s == 1) {
s0_s = 5;
}
else if (s0_s == 4) {
s0_s = 9;
}
else if (s0_s == 36) {
s0_s = 38;
}
else if (s0_s == 37) {
s0_s = 40;
}
else if (s0_s == 39) {
s0_s = 41;
}
if (s3_s == 0) {
s3_s = 1;
}
else if (s3_s == 5) {
s3_s = 1;
}
else if (s3_s == 6) {
s3_s = 1;
}
else if (s3_s == 10) {
s3_s = 1;
}
move_0();
}

else if (decided_action == EVENT_C_MOVE_1) {
if (s0_s == 26) {
s0_s = 28;
}
else if (s0_s == 27) {
s0_s = 30;
}
else if (s0_s == 29) {
s0_s = 32;
}
if (s3_s == 0) {
s3_s = 2;
}
else if (s3_s == 6) {
s3_s = 2;
}
else if (s3_s == 10) {
s3_s = 2;
}
move_1();
}

else if (decided_action == EVENT_C_MOVE_2) {
if (s0_s == 16) {
s0_s = 18;
}
else if (s0_s == 17) {
s0_s = 20;
}
else if (s0_s == 19) {
s0_s = 22;
}
if (s3_s == 0) {
s3_s = 3;
}
else if (s3_s == 5) {
s3_s = 3;
}
else if (s3_s == 10) {
s3_s = 3;
}
move_2();
}

else if (decided_action == EVENT_C_MOVE_3) {
if (s0_s == 0) {
s0_s = 3;
}
else if (s0_s == 1) {
s0_s = 6;
}
else if (s0_s == 4) {
s0_s = 10;
}
else if (s0_s == 7) {
s0_s = 3;
}
else if (s0_s == 11) {
s0_s = 6;
}
else if (s0_s == 13) {
s0_s = 10;
}
if (s3_s == 8) {
s3_s = 9;
}
move_3();
}

else if (decided_action == EVENT_C_CLOSE_FLOOR) {
if (s1_s == 0) {
s1_s = 1;
}
if (s2_s == 2) {
s2_s = 3;
}
close_floor();
}

else if (decided_action == EVENT_C_INPUT_PALLET) {
if (s3_s == 4) {
s3_s = 7;
}
input_pallet();
}

else if (decided_action == EVENT_C_INPUT_BOX) {
if (s2_s == 0) {
s2_s = 1;
}
else if (s2_s == 4) {
s2_s = 5;
}
else if (s2_s == 6) {
s2_s = 8;
}
input_box();
}

else if (decided_action == EVENT_C_FIT_BOX) {
if (s0_s == 0) {
s0_s = 1;
}
else if (s0_s == 2) {
s0_s = 5;
}
else if (s0_s == 3) {
s0_s = 6;
}
else if (s0_s == 7) {
s0_s = 11;
}
else if (s0_s == 8) {
s0_s = 12;
}
else if (s0_s == 16) {
s0_s = 17;
}
else if (s0_s == 18) {
s0_s = 20;
}
else if (s0_s == 21) {
s0_s = 23;
}
else if (s0_s == 26) {
s0_s = 27;
}
else if (s0_s == 28) {
s0_s = 30;
}
else if (s0_s == 31) {
s0_s = 33;
}
else if (s0_s == 36) {
s0_s = 37;
}
else if (s0_s == 38) {
s0_s = 40;
}
if (s1_s == 2) {
s1_s = 3;
}
fit_box();
}

else if (decided_action == EVENT_C_OPEN_FLOOR) {
if (s1_s == 4) {
s1_s = 5;
}
if (s2_s == 4) {
s2_s = 6;
}
else if (s2_s == 5) {
s2_s = 8;
}
else if (s2_s == 7) {
s2_s = 9;
}
open_floor();
}

else if (decided_action == EVENT_C_RELEASE_BOX) {
if (s0_s == 14) {
s0_s = 15;
}
else if (s0_s == 24) {
s0_s = 25;
}
else if (s0_s == 34) {
s0_s = 35;
}
if (s1_s == 6) {
s1_s = 7;
}
release_box();
}

}
/************************/
/***** INTERRUPT ********/
unsigned int tick;

void interrupt ISR_interrupt() {
    if (RCIF) { // test the interrupt for uart rx
        const unsigned char c = RCREG;

        if (c == 244) {
            input_box();
        }
        if (c == 10) {
            TURN_OFF_S0;
        } else if (c == 11) {
            TURN_OFF_S1;
        } else if (c == 12) {
            TURN_OFF_S2;
        } else if (c == 13) {
            TURN_OFF_S3;
        } else if (c == 14) {
            TURN_OFF_S4;
        } else if (c == 15) {
            TURN_OFF_S5;
        } else if (c == 16) {
            TURN_OFF_S6;
        } else if (c == 17) {
            TURN_OFF_S7;
        } else if (c == 18) {
            TURN_OFF_S8;
        } else if (c == 19) {
            TURN_OFF_S9;
        } else if (c == 20) {
            TURN_OFF_S10;
        } else if (c == 110) {
            TURN_ON_S0;
        } else if (c == 111) {
            TURN_ON_S1;
        } else if (c == 112) {
            TURN_ON_S2;
        } else if (c == 113) {
            TURN_ON_S3;
        } else if (c == 114) {
            TURN_ON_S4;
        } else if (c == 115) {
            TURN_ON_S5;
        } else if (c == 116) {
            TURN_ON_S6;
        } else if (c == 117) {
            TURN_ON_S7;
        } else if (c == 118) {
            TURN_ON_S8;
        } else if (c == 119) {
            TURN_ON_S9;
        } else if (c == 120) {
            TURN_ON_S10;
        }

        CREN = 0;
        CREN = 1;
    }
    if (TMR0IF) {
        tick += 16 * 2;
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


    // setup interrupts for Async USART
    IPEN = 1; // enable priority //(mid-range compatibility)
    GIEH = 1; // enables all interrupts that have the priority bit set
    GIEL = 1; // enables all interrupts that have the priority bit cleared
    PEIE = 1; // enables/disables all peripheral interrupt sources

    // setup Async USART for receive
    RCIE = 1;
    SPEN = 1;
    TRISC = 0;
    SetBit(TRISC, 7);
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

    /* Initialize variables */
    S.bytes.byte1 = 0;
    S.bytes.byte2 = 0;
    A.byte = 0;
    membank0.byte = 0;
    membank1.byte = 0;
    membank2.byte = 0;
    tmembank.byte = 0;

    events_n_todo_count = 0;
    tick = 0;
    seconds = 0;

    s0_s = 0;
    s1_s = 0;
    s2_s = 0;
    s3_s = 0;

    unsigned char lcd_refresh_rate = 255;

    while (1) {

	sup_response_step();
	
	des_step();

	decisions_step();

	sup_advance_step();

        update_input_box();
        update_input_pallet();
        update_move_0();
        update_move_1();
        update_move_2();
        update_move_3();
        update_fit_box();
        update_release_box();
        update_open_floor();
        update_close_floor();

        lcd_refresh_rate--;
        if (lcd_refresh_rate == 0) {
            lcd_update(S, A);
            lcd_refresh_rate = 255;
        }
    }
}

