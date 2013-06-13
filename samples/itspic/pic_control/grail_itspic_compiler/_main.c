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

