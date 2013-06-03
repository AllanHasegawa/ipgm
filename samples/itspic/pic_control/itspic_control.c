#include <pic18f6520.h>

#pragma config WDT=OFF

#define SetBit(v,bit) v |= (1 << bit);
#define ClearBit(v,bit) v &= ~(1 << bit);
#define IsSetBit(v,bit) ((v & (1 << bit)) > 0)

#define IS_S0 IsSetBit(PORTD, 0)
#define IS_S1 IsSetBit(PORTD, 1)
#define IS_S2 IsSetBit(PORTD, 2)
#define IS_S3 IsSetBit(PORTD, 3)
#define IS_S4 IsSetBit(PORTD, 4)

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
	while(1) {
		if (IsSetBit(PORTE,2)) {
			SetBit(PORTB,2);
		} else {
			ClearBit(PORTB,2);
		}
		if (IS_S0) {
			SetBit(PORTB,1);
		} else {
			ClearBit(PORTB,1);
		}
	}
}

