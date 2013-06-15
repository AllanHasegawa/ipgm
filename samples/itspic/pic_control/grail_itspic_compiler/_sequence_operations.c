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

unsigned int elevator_tmr;
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
	    elevator_tmr = seconds;
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
        } else {
		if (bELEVATOR_P2){
		if (elevator_tmr > seconds) {
			elevator_tmr = seconds;
		}
		if ((elevator_tmr + 2) < seconds) {
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
    }
}

void move_2(void) {
    if (!bMOVE_2_ACTIVE) {
        if (bELEVATOR_P0
                || bELEVATOR_P1) {
            ELEVATOR_UP;
        } else {
		elevator_tmr = seconds;
            ELEVATOR_DOWN;
        }
        bMOVE_2_ACTIVE = 1;
    }
}

void update_move_2(void) {
    if (bMOVE_2_ACTIVE) {
        if (ELEVATOR_IS_P2 || ELEVATOR_IS_P1) {
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
        } else {
		if (bELEVATOR_P3) {
		if (elevator_tmr > seconds) {
			elevator_tmr = seconds;
		}
		if ((elevator_tmr + 2) < seconds) {
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
	bFIT_BOX_FITTING = 0;
    }
}

unsigned int fitting_box_tmr;
void update_fit_box(void) {
    if (bFIT_BOX_ACTIVE) {
        if (IS_BOX_FITTED) {
		if (bFIT_BOX_FITTING == 0) {
			bFIT_BOX_FITTING = 1;
			fitting_box_tmr = seconds;
		} else {
			if (fitting_box_tmr > seconds) {
				fitting_box_tmr = seconds;
			}
			if ((fitting_box_tmr+4) < seconds) {
		            // end_fit_box
		            bFIT_BOX_ACTIVE = 0;
		            RAISE_EVENT_N_END_FIT_BOX;
			}
		}
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
#define OPEN_FLOOR TURN_OFF_A3
#define CLOSE_FLOOR TURN_ON_A3
#define FREE_BOX TURN_ON_A2
#define BLOCK_BOX TURN_OFF_A2
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

unsigned int close_floor_tmr;
void close_floor(void) {
    if (!bCLOSE_FLOOR_ACTIVE) {
        bCLOSE_FLOOR_ACTIVE = 1;
        CLOSE_FLOOR;
	close_floor_tmr = seconds;
	bCLOSE_FLOOR_BOX_FREE = 0;
    }
}

void update_close_floor(void) {
    if (bCLOSE_FLOOR_ACTIVE) {
	if (!bCLOSE_FLOOR_BOX_FREE) {
		if (close_floor_tmr > seconds) {
			close_floor_tmr = seconds;
		}
		if ((close_floor_tmr + 1) < seconds) {
			FREE_BOX;
			bCLOSE_FLOOR_BOX_FREE = 1;
			close_floor_tmr = seconds;
		}
	} else {
		if (close_floor_tmr > seconds) {
			close_floor_tmr = seconds;
		}
		if ((close_floor_tmr + 5) < seconds) {
			BLOCK_BOX;
			RAISE_EVENT_N_END_MID_CLOSE_FLOOR;	
		}
	}
        if (IS_FLOOR_CLOSED) {
            // end_close_floor
            bCLOSE_FLOOR_ACTIVE = 0;
            RAISE_EVENT_N_END_CLOSE_FLOOR;
	    BLOCK_BOX;
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


unsigned int input_box_tmr2;
unsigned int input_box_tmr3;
void input_box(void) {
    if (!bINPUT_BOX_ACTIVE) {
        TURN_ON_UP_BOX;
	input_box_tmr2 = seconds;
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
                if ((input_box_tmr + 5) < seconds) {
                    // end_input_box
                    bINPUT_BOX_ACTIVE = 0;
                    RAISE_EVENT_N_END_INPUT_BOX;
		    SERIAL_TX(244);
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
                } else {
			if (input_box_tmr3 > seconds) {
				input_box_tmr3 = seconds;
			}
			if ((input_box_tmr3 + 20) < seconds) {
				TURN_OFF_PUSH_BOX;
		                    if (bINPUT_BOX_FIRST) {
                		        input_box_tmr = 0;
		                        bINPUT_BOX_SECOND = 1;
                		        TURN_OFF_UP_BOX;
                		    } else {
		                        bINPUT_BOX_FIRST = 1;
                		    }
			}
		}
            } else {
		if (input_box_tmr2 > seconds) {
			input_box_tmr2 = seconds;
		}
		if ((input_box_tmr2 + 40) < seconds) {
			TURN_ON_PUSH_BOX;
			input_box_tmr3 = seconds;
			input_box_tmr2 = seconds;
		}
                if (IS_S0) {
                    TURN_ON_PUSH_BOX;
		    input_box_tmr3 = seconds;
		    input_box_tmr2 = seconds;
                }
            }
        }
    }
}

