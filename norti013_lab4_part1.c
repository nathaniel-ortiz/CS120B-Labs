#include <avr/io.h>

int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputB = 0x00;
	unsigned char state = 0x00;
	
	while(1) {
		
		switch(state) {
			case 0:
				inputA = PINA;
				outputB = 0x01;
				if(inputA = 0x01) {
					state = 1;
				}
				PORTB = outputB;
				break;
				
			case 1:
				inputA = PINA;
				outputB = 0x02;
				if(inputA = 0x01) {
					state = 0;
				}
				PORTB = outputB;
				break;
				
			default:
				outputB = 0x00;
				PORTB = outputB;
		}
	}
}