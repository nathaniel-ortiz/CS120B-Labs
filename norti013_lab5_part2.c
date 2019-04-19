#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0x00; PORTC = 0xFF;
	DDRA = 0xFF; PORTA = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputC = 0x00;
	unsigned char state = 0;
	
	while (1)
	{
		switch(state) {
			case 0:
			outputC = 0x07;
			PORTA = outputC;
			state = 1;
			break;
			case 1:
			inputA = ~PINC;
			if(inputA == 0x01) { //pin 0 high
				state = 2;
			}
			else if(inputA == 0x02) { //pin 1 high
				state = 3;
			}
			else if(inputA == 0x03) { //pin 1 and 0 high
				state = 4;
			}
			else {
				state = 5;
			}
			break;
			case 2:
			if(outputC != 0x09) {
				++outputC;
				PORTA = outputC;
				state = 6;
			}
			else {
				PORTA = outputC;
				state = 6;
			}
			break;
			case 3:
			if(outputC != 0x00) {
				--outputC;
				PORTA = outputC;
				state = 6;
			}
			else {
				PORTA = outputC;
				state = 6;
			}
			break;
			case 4:
			outputC = 0;
			PORTA = outputC;
			
			state = 6;
			break;
			case 5:
			state = 1;
			break;
			case 6:
			_delay_ms(1000);
			state = 1;
			break;
			default:
			outputC = 0xFF;
			PORTA = outputC; //should never be reached
			break;
		}
	}
}
