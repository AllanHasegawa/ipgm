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
#define RAISE_EVENT_N_END_MID_CLOSE_FLOOR events_n_todo[events_n_todo_count++] = EVENT_N_END_MID_CLOSE_FLOOR;
#define RAISE_EVENT_N_END_CLOSE_FLOOR events_n_todo[events_n_todo_count++] = EVENT_N_END_CLOSE_FLOOR;
#define RAISE_EVENT_N_END_FIT_BOX events_n_todo[events_n_todo_count++] = EVENT_N_END_FIT_BOX;
#define RAISE_EVENT_N_END_INPUT_BOX events_n_todo[events_n_todo_count++] = EVENT_N_END_INPUT_BOX;
#define RAISE_EVENT_N_END_RELEASE_BOX events_n_todo[events_n_todo_count++] = EVENT_N_END_RELEASE_BOX;
#define RAISE_EVENT_N_END_INPUT_PALLET events_n_todo[events_n_todo_count++] = EVENT_N_END_INPUT_PALLET;

