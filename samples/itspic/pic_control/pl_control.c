#include <pic18f452.h>
#include <stdio.h>

#pragma config WDT=OFF

#define SetBit(v,bit) v |= (1 << bit);
#define ClearBit(v,bit) v &= ~(1 << bit);
#define IsSetBit(v,bit) ((v & (1 << bit)) >> bit)

void atraso_ms(unsigned int valor)
{
unsigned int  i;
unsigned char j;
unsigned char k;
 for (i =0; i< valor; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
	   k = 0;
	  /*
     _asm
	NOP
	NOP
	NOP
	NOP
	NOP
    _endasm;*/
   }
 }
}

void serial_init(void)
{
	//Configuracao da serial
    TXSTAbits.TX9=1;    //transmissao em 8 bits
    TXSTAbits.TXEN=1;  //habilita transmissao
    TXSTAbits.SYNC=1;  //modo assincrono
    TXSTAbits.BRGH=1;  //high baud rate
    RCSTAbits.SPEN=1;  //habilita porta serial - rx
    RCSTAbits.RX9=0;   //recepcao em 8 bits
    RCSTAbits.CREN=1;  //recepcao continua

    SPBRG=25; //baud rate de 9600 - 4MHz
}

void serial_tx(unsigned char val)
{
  TXREG=val;
  while(!TXSTAbits.TRMT);
}

void serial_tx_str(const char* val)
{
  unsigned char i=0;
  
  while(val[i])
  {
    serial_tx(val[i]);
    i++; 
  }
}

unsigned char serial_rx(unsigned int timeout)
{
  unsigned int to=0;

  while(((to < timeout)||(!timeout))&&(!PIR1bits.RCIF))
  {
    atraso_ms(20);
    to+=20; 
  }
  if(PIR1bits.RCIF)
    return RCREG;
  else
    return 255;
}

PUTCHAR( c ) {
	PORTC = c;
}

void main(void) {
	char str[6];

	SetBit(RCSTA,7);
	SetBit(TRISC,7);
	ClearBit(TRISC,6);
	//serial_init();
	stdout = STREAM_USER;


	//serial_tx_str("lolala\n");
	//
	printf("Hi\n");
	while(1);
}
