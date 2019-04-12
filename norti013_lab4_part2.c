#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputC = 0x00;
	unsigned char state = 0;
	
    while (1) 
    {
		switch(state) {
			case 0:
				outputC = 0x07;
				PORTC = outputC;
				state = 1;
				break;
			case 1:
				inputA = PINA;
				if(inputA == 0x01) { //pin 0 high
					state = 2;
				}
				else if(inputA == 0x02) { //pin 1 high
					state = 3;
				}
				else if(inputA == 0x03) { //pin 1 and 0 high
					state = 4;
				}
				break;
			case 2:
				if(outputC < 9) {
					outputC++;
					PORTC = outputC;
					state = 1;
				}
				else {
					PORTC = outputC;
					state = 1;
				}
				break;
			case 3:
				if(outputC > 0) {
					outputC--;
					PORTC = outputC;
					state = 1;
				}
				else {
					PORTC = outputC;
					state = 1;
				}
				break;
			case 4:
				outputC = 0;
				PORTC = outputC;
				
				state = 1;
				break;
			default:
				outputC = 0xFF;
				PORTC = outputC; //should never be reached
				break;
		}
    }
}

