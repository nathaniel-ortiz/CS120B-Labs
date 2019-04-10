#include <avr/io.h>

int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char inputB = 0x00;
	unsigned char outputC = 0x00;
	
	while(1) {
		
		inputA = PINA;
		inputB = PINB;
		
		for(int i = 0; i < 8; i++) {
			if((inputA & 0x01) == 0x01) {
				outputC++;
			}
			inputA = inputA >> 1;
		}
		
		for(int i = 0; i < 8; i++) {
			if((inputB & 0x01) == 0x01) {
				outputC++;
			}
			inputB = inputB >> 1;
		}
		
		PORTC = outputC;
	}
}