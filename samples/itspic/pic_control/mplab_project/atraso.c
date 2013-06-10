#include "atraso.h"

void atraso_ms(unsigned int valor) {
    unsigned int i;
    unsigned char j;
    char k;

    for (i = 0; i < valor; i++) {
        for (j = 0; j < 200; j++) {
           k++;
           k++;
           k++;
           k++;
           k = 0;
            /*_asm
               NOP
               NOP
               NOP
               NOP
               NOP
           _endasm;*/
        }
    }
}
