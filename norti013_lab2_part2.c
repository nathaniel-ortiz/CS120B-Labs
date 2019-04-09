#include <avr/io.h>

/*
0 = 0x00
1 = 0x01
2 = 0x02
3 = 0x03
4 = 0x04
5 = 0x05
6 = 0x06
7 = 0x07
8 = 0x08
9 = 0x09
10 = 0x0A
11 = 0x0B
12 = 0x0C
13 = 0x0D
14 = 0x0E
15 = 0x0F
*/

int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputC = 0x00;
	
	while(1) {
		
		inputA = PINA;
		
		if(inputA == 0x00) {
			outputC = 0x40;
		}
		
		else if(inputA == 0x01 || inputA == 0x02) {
			outputC = 0x60;
		}
		
		else if(inputA == 0x03 || inputA == 0x04) {
			outputC = 0x70;
		}
		
		else if(inputA == 0x05 || inputA == 0x06) {
			outputC = 0x38;
		}
		
		else if(inputA == 0x07 || inputA == 0x08 || inputA == 0x09) {
			outputC = 0x3C;
		}
		
		else if(inputA == 0x0A || inputA == 0x0B || inputA == 0x0C) {
			outputC = 0x03E;
		}
		
		else if(inputA == 0x0D || inputA == 0x0E || inputA == 0x0F) {
			outputC == 0x3F;
		}
		
		PORTC = outputC;
	}
}