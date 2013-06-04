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
#define IS_S5 IsSetBit(PORTD, 5)
#define IS_S6 IsSetBit(PORTD, 6)
#define IS_S7 IsSetBit(PORTD, 7)
#define IS_S8 IsSetBit(PORTE, 0)
#define IS_S9 IsSetBit(PORTE, 1)
#define IS_S10 IsSetBit(PORTE, 2)
#define IS_S11 IsSetBit(PORTE, 3)

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
