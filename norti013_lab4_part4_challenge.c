#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputB = 0x00;
	unsigned char outputC = 0x00;
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
			if(PINA == 0x04) {
				state = 2;
			}
			else if(PINA == 0x80) {
				outputB = 0x00;
				PORTB = outputB;
				state = 0;
			}
			else {
				state = 0;
			}
			break;
			
			case 2:
			inputA = PINA;
			outputC = state;
			PORTC = outputC;
			if(PINA == 0x02) {
				state = 3;
			}
			else if(PINA == 0x80) {
				outputB = 0x00;
				PORTB = outputB;
				state = 0;
			}
			else {
				state = 0;
			}
			break;
			
			case 3:
			inputA = PINA;
			if(PINA == 0x80) {
				outputB = 0x00;
				PORTB = outputB;
				state = 0;
			}
			else {
				outputB = 0x01;
				PORTB = outputB;
				state = 4;
			}
			break;
			
			case 4:
			inputA = PINA;
			if(inputA == 0x04) {
				state = 5;
				
			}
			else if(inputA == 0x80) {
				state = 0;	
			}
			else {
				state = 3;
				
			}
			break;
			
			case 5:
				inputA = PINA;
				if(inputA == 0x02) {
					state = 6;
				}
				else if(inputA == 0x80) {
					state = 0;
				}
				else {
					state = 3;
				}
				break;
			case 6:
				inputA = PINA;
				if(inputA == 0x80) {
					state = 0;
				}
				else {
					outputB = 0x00;
					PORTB = outputB;
					state = 0;
				}
				break;
		}
		
	}
}

