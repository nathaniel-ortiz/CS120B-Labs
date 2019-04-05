#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs
	// Initialize output on PORTB to 0x00
	unsigned char inputA = 0x00;
	unsigned char outputC = 0x00;
	while(1)
	{
		unsigned char numSpaces = 0;
		inputA = PINA;
		
		for(int i = 0; i < 4; i++) {
			if((inputA & 0x01) == 0x01) { //AND inputA with 1 to ensure only first bit is high
				numSpaces++; //increment number of spaces in use if first bit is high
			}
			inputA = inputA >> 1; //right shift inputA after checking
			outputC = numSpaces;
		}
		
		if(outputC == 0x04) {
			outputC = outputC | 0x80;
		}
		
		PORTC = outputC;
	}
}
