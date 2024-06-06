#include <avr/interrupt.h>
uint8_t digit[] = {0xA0, 0xBB, 0x62, 0x2A, 0x39, 0x2C, 
0x24, 0xBA, 0x20, 0x28, 0x70, 0x64, 0x37};
uint8_t num[4] = {0, 0, 0, 0};
ISR (TIMER0_COMPA_vect) {
	static uint8_t i = 0;
	PORTB = 0xFF;	
	PORTD = digit [num[i]];
	PORTB &= ~_BV(i) ;	
if (i < 4) i++;	
else i=0;
}
ISR (TIMER1_COMPA_vect) {
static uint8_t y = 0;
if (y==0){
if (num[0] == 9)
{ num[0] = 0;
 num[1]=num[1]+1;}
else num[0]=num[0]+1;
if ((num[0] == 0) && (num[1] == 3))
{ 	num[0]=12;
	num[1]=11;
	num[2]=10;
	num[3]=0;
	y=1; 
}}}
int main() {
	DDRB = 0xFF;
	DDRD = 0xFF;
	TCCR0A |= _BV(WGM01);
	OCR0A = 40;
	TIMSK0 |= _BV(OCIE0A);
	TCCR0B |= _BV(CS01)|_BV(CS00);
          TCCR1B |= _BV(WGM12);
	OCR1A = 7812;
	TIMSK1 |= _BV(OCIE1A);
	TCCR1B |= _BV(CS11)|_BV(CS10);
	sei();
while(1) {};
}
