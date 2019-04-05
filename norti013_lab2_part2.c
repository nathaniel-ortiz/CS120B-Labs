#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
					// Initialize output on PORTB to 0x00
	unsigned char inputA = 0x00;
	unsigned char outputB = 0x00
	while(1)
	{
		inputA = PINA;
		if(inputA == 0x01) {
			outputB == 0x01;
		}
		else {
			outputB == 0x00;
		}
		PORTB = outputB;
	}
}
