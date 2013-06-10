/* 
 * File:   mylcd.h
 * Author: AranHase
 *
 * Created on June 9, 2013, 11:21 PM
 */

#ifndef MYLCD_H
#define	MYLCD_H
#include "datatypes.h"
#include "lcd.h"
#include "itoa.h"

char lcd_sensors_str[4];
char lcd_actuators_str[4];
char lcd_sensors_list_str[12];
char lcd_actuators_list_str[9];

void rom2ram(const char *pdata, char* buffer) {
    unsigned char n = 0;
    char c;
    while (c = pdata[n]) {
        buffer[n] = c;
        n++;
    }
    buffer[n] = '\0';
}

void mylcd_init() {

    lcd_init();
    rom2ram("SE ", lcd_sensors_str);
    rom2ram("AC ", lcd_actuators_str);
}

void update_sensor_list(const sensors S, char* buffer) {
    unsigned char n = 0;
    buffer[n++] = S.id.b00 ? '1' : '0';
    buffer[n++] = S.id.b01 ? '1' : '0';
    buffer[n++] = S.id.b02 ? '1' : '0';
    buffer[n++] = S.id.b03 ? '1' : '0';
    buffer[n++] = S.id.b04 ? '1' : '0';
    buffer[n++] = S.id.b05 ? '1' : '0';
    buffer[n++] = S.id.b06 ? '1' : '0';
    buffer[n++] = S.id.b07 ? '1' : '0';
    buffer[n++] = S.id.b08 ? '1' : '0';
    buffer[n++] = S.id.b09 ? '1' : '0';
    buffer[n++] = S.id.b10 ? '1' : '0';

    buffer[n++] = '\0';
}

void update_actuators_list(const bybit A, char* buffer) {
    unsigned char n = 0;
    buffer[n++] = A.bits.b0 ? '1' : '0';
    buffer[n++] = A.bits.b1 ? '1' : '0';
    buffer[n++] = A.bits.b2 ? '1' : '0';
    buffer[n++] = A.bits.b3 ? '1' : '0';
    buffer[n++] = A.bits.b4 ? '1' : '0';
    buffer[n++] = A.bits.b5 ? '1' : '0';
    buffer[n++] = A.bits.b6 ? '1' : '0';
    buffer[n++] = A.bits.b7 ? '1' : '0';

    buffer[n++] = '\0';
}

void lcd_update(const sensors s, const bybit ac) {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str(lcd_sensors_str);
    update_sensor_list(s, lcd_sensors_list_str);
    lcd_str(lcd_sensors_list_str);
    lcd_cmd(L_L2);
    lcd_str(lcd_actuators_str);
    update_actuators_list(ac, lcd_actuators_list_str);
    lcd_str(lcd_actuators_list_str);
}


#endif	/* MYLCD_H */

