// keep state of sensors and actuators
sensors S;
bybit A;

// keep a queue of events non-controlable todo
unsigned char events_n_todo[40];
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
#define bCLOSE_FLOOR_BOX_FREE membank2.bits.b1
#define bFIT_BOX_FITTING membank2.bits.b2
bybit membank2;
bybit tmembank;

