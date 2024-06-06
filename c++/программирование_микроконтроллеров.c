// Вариант кодовый замок (вариант с конпками ) AVR Dracon ,Atmega 88
#include <avr/interrupt.h>

//Массив состояния кнопок
uint8_t btns[4][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};
const uint8_t symbols[] = {0xff, 0xbb, 0x62, 0x2a, 0x39, 0x2c, 0x24, 0xba, 0x20, 0x28, 0x70, 0xa0, 0x64, 0xb0};
uint8_t indicator[] = {0, 0, 0, 0};
uint8_t flag = 0;
uint8_t num = 0;

ISR(TIMER0_COMPA_vect){
	static uint8_t i = 0;
	static uint8_t deb = 0;
	static uint8_t keys = 11;

	PORTB |= _BV(0)|_BV(1)|_BV(2)|_BV(3);
	PORTD = symbols[indicator[3-i]];
	PORTB &= ~_BV(i);

	i++;

	if (i == 4){
		i = 0;
	};


	deb++;

	if (deb == 24){
		deb = 0;
		for (uint8_t i = 4; i < 7; i++){
			PORTC |= _BV(5);	//Установка C5 в 1
			PORTB |= _BV(5)|_BV(4); //Установка B5 и B4 в 1
			if (i < 6) PORTB &= ~_BV(i);	//Установка B5 или B4 в 0
			else PORTC &= ~_BV(i-1); 	//Установка C5 в 0
			for (int8_t d = 0; d < 4; d++){ //Цикл чтения состояния кнопок из порта C
				if (bit_is_clear(PINC, d)) {
					if (btns[d][2-(i-4)] == 0){ //Если вход порта C в состоянии 0, то запись в массив состояния кнопок 1
						btns[d][2-(i-4)] = 1;
						flag = 1;
						num = 1+(2-(i-4))+d*3;
					}
				}
				else btns[d][2-(i-4)] = 0;
			}
		}
	}
}

int main(){
	
	DDRD = 0xff;
	DDRB |= _BV(0)|_BV(1)|_BV(2)|_BV(3)|_BV(4)|_BV(5);
	DDRC |= _BV(5);

	TCCR0A |= _BV(WGM01);
	TCCR0B |= _BV(CS00)|_BV(CS01);
	OCR0A = 65;
	TIMSK0 |= _BV(OCIE0A);

	sei();

	while(1){
		if (flag){ //Если кнопка нажата
			flag = 0;
			indicator[0] = indicator[1];
			indicator[1] = indicator[2];
			indicator[2]=indicator[3];
			indicator[3]=num;
		}
	}
}
