#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputB = 0x00;
	unsigned char outputC = 0x00;
	unsigned char pattern[4] = {0x04, 0x01, 0x02, 0x01};
	unsigned char state = 0;
		
    while (1) 
    {
		switch(state) {
			case 0:
				outputB = 0x00;
				outputC = 0x00;
				PORTB = outputB;
				PORTC = outputC;
				state = 1;
				break;
			case 1:
				inputA = PINA;
				outputC = state;
				PORTC = outputC;
				if(inputA == pattern[0]) {
					state = 2;
				}
				else if(inputA == 0x80) {
					state = 0;
				}
				else {
					state = 1;
				}
				break;
			case 2:
				inputA = PINA;
				outputC = state;
				PORTC = outputC;
					if(inputA == pattern[1]) {
						state = 3;
					}
					else if(inputA == 0x80) {
						state = 0;
					}
					else {
						state = 1;
					}
					break;
			case 3:
				inputA = PINA;
				outputC = state;
				PORTC = outputC;
					if(inputA == pattern[2]) {
						state = 4;
					}
					else if(inputA == 0x80) {
						state = 0;
					}
					else {
						state = 1;
					}
					break;
			case 4:
				inputA = PINA;
				outputC = state;
				PORTC = outputC;
					if(inputA == pattern[3]) {
						state = 5;
					}
					else if(inputA == 0x80) {
						state = 0;
					}
					else {
						state = 1;
					}
					break;
				case 5:
					if(outputB == 0x01) {
						outputB = 0x00;
					}
					else if(outputB == 0x00) {
						outputB = 0x01;
					}
					PORTB = outputB;
					state = 1;
					break;
		}
	}
}

