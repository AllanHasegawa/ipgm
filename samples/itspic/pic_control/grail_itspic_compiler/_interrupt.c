/************************/
/***** INTERRUPT ********/
unsigned int tick;

void interrupt ISR_interrupt() {
    if (RCIF) { // test the interrupt for uart rx
        const unsigned char c = RCREG;

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
        tick += 128;//16 * 2;
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

