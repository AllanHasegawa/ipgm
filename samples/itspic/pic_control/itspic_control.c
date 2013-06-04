#include <pic18fregs.h>

#pragma config WDT=OFF,CP0=OFF,OSCS=ON,OSC=LP,BOR=ON,BORV=25,WDTPS=128,CCP2MUX=ON
//#pragma config OSCS=ON
//#pragma config OSC=LP

#define SetBit(v,bit) v |= (1 << bit);
#define ClearBit(v,bit) v &= ~(1 << bit);
#define IsSetBit(v,bit) ((v & (1 << bit)) >> bit)

#define IS_S0 IsSetBit(PORTD, 0)
#define IS_S1 IsSetBit(PORTD, 1)
#define IS_S2 IsSetBit(PORTD, 2)
#define IS_S3 IsSetBit(PORTD, 3)
#define IS_S4 IsSetBit(PORTD, 4)
#define IS_S5 IsSetBit(PORTD, 5)
#define IS_S6 IsSetBit(PORTD, 6)
#define IS_S7 IsSetBit(PORTD, 7)
#define IS_S8 IsSetBit(PORTE, 0)
#define IS_S9 IsSetBit(PORTE, 1)
#define IS_S10 IsSetBit(PORTE, 2)

#define IS_A0 IsSetBit(PORTB, 0)
#define IS_A1 IsSetBit(PORTB, 1)
#define IS_A2 IsSetBit(PORTB, 2)
#define IS_A3 IsSetBit(PORTB, 3)
#define IS_A4 IsSetBit(PORTB, 4)
#define IS_A5 IsSetBit(PORTB, 5)
#define IS_A6 IsSetBit(PORTB, 6)
#define IS_A7 IsSetBit(PORTB, 7)

#define TURN_ON_A0 SetBit(PORTB, 0)
#define TURN_ON_A1 SetBit(PORTB, 1)
#define TURN_ON_A2 SetBit(PORTB, 2)
#define TURN_ON_A3 SetBit(PORTB, 3)
#define TURN_ON_A4 SetBit(PORTB, 4)
#define TURN_ON_A5 SetBit(PORTB, 5)
#define TURN_ON_A6 SetBit(PORTB, 6)
#define TURN_ON_A7 SetBit(PORTB, 7)

#define TURN_OFF_A0 ClearBit(PORTB, 0)
#define TURN_OFF_A1 ClearBit(PORTB, 1)
#define TURN_OFF_A2 ClearBit(PORTB, 2)
#define TURN_OFF_A3 ClearBit(PORTB, 3)
#define TURN_OFF_A4 ClearBit(PORTB, 4)
#define TURN_OFF_A5 ClearBit(PORTB, 5)
#define TURN_OFF_A6 ClearBit(PORTB, 6)
#define TURN_OFF_A7 ClearBit(PORTB, 7)


typedef union
{
  unsigned char byte;
  struct
  {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
  } bits;
} bybit;

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

/*************************************************/


//#pragma udata bigarray supervisor
void* nodes_functions_cache[62];

void main(void) {
	// PORTD pin 0-7 are INPUT
	TRISD = 0b11111111;
	// PORTE pin 0-7 are INPUT
	TRISE = 0b11111111;
	// PORTB pin 0-7 is OUTPUT
	TRISB = 0b00000000;

	// Compatibility with gpsim
	//   (only output ports are updated)
	// It can now shows digitial on Breadboard
	TRISD = 0;
	TRISE = 0;

	// Reseting ports
	PORTB = 0;
	PORTD = 0;
	PORTE = 0;

	membank0.byte = 0;
	membank1.byte = 0;
	membank2.byte = 0;
	tmembank.byte = 0;

	while(1) {
		if (IS_S8) {
			membank2.bits.b2 = 1;
		} else {
			if (membank2.bits.b2) {
				fit_box();
				membank2.bits.b2 = 0;
			}
		}
		if (IS_S9) {
			membank2.bits.b3 = 1;
		} else {
			if (membank2.bits.b3) {
				release_box();
				membank2.bits.b3 = 0;
			}
		}
		
		update_input_pallet();
		update_move_0();
		update_move_1();
		update_move_2();
		update_move_3();
		update_fit_box();
		update_release_box();
		update_open_floor();
		update_close_floor();
	}
}

