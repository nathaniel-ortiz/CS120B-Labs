#include <avr/io.h>


int main(void)
{
	DDRB = 0xFE; PORTB = 0x01;
	DDRD = 0x00; PORTD = 0xFF;
	
	unsigned short totalWeight = 0;
	unsigned char inputB = 0x00;
	unsigned char outputB = 0x00;
	unsigned char inputD = 0x00;
	
    while (1) 
    {
		
		inputD = PIND;
		inputB = PINB & 0x01; //and'ing to ensure that only the first bit of pin B is being interpreted as the input
		
		totalWeight = inputD;
		totalWeight = totalWeight << 1;
		totalWeight = totalWeight | inputB;
		
		if(totalWeight >= 70) {
			outputB = 0x02;
		}
		
		else if(totalWeight < 70 && totalWeight > 5) {
			outputB = 0x04;
		}
		
		else {
			outputB = 0x00;
		}
		
		PORTB = outputB | PINB; //or with the input to avoid modifying the input
	}
}

