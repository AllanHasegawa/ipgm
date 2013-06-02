#include <pic18f6520.h>

#pragma config WDT=OFF

#define SetBit(v,bit) v |= (1 << bit);
#define ClearBit(v,bit) v &= ~(1 << bit);

void main(void) {
	// PORTD pin 0-7 are INPUT
	TRISD = 0b11111111;
	// PORTE pin 0-7 are INPUT
	TRISE = 0b11111111;
	// PORTB pin 0-7 is OUTPUT
	TRISB = 0b00000000;

	// Compatibility with gpsim
	// It can now shows digitial on Breadboard
	TRISD = 0;
	TRISE = 0;

	// Reseting ports
	PORTB = 0;
	PORTD = 0;
	PORTE = 0;
	while(1) {
		if (PORTE & (1 << 2)) {
			SetBit(PORTB,0);
		} else {
			ClearBit(PORTB,0);
		}
		if (PORTD & (1 << 1)) {
			SetBit(PORTB,1);
		} else {
			ClearBit(PORTB,1);
		}
	}
}

