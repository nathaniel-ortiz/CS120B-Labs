#include <avr/io.h>
//write to PORTS
//read from PINS

int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	int totalWeight = 0;
	int diffWeight = 0;
	int inputA = 0;
	int inputB = 0;
	int inputC = 0;
	unsigned char outputD = 0x00;
	
	while (1) {
		inputA = PINA;
		inputB = PINB;
		inputC = PINC;
		
		totalWeight = inputA + inputB + inputC;
		
		if(totalWeight > 140) {
			outputD = 0x01;
		}
		
		if(inputA > inputC) {
			diffWeight = inputA - inputC;
		}
		else {
			diffWeight = inputC - inputA;
		}
		
		if(diffWeight > 80) {
			outputD = outputD | 0x02;
		}
		
		totalWeight = totalWeight / 64;
		totalWeight = totalWeight << 1;
		totalWeight = totalWeight << 1; //bitshift left twice to use the remaining 6 bits to represent the rider's approx weight
		
		outputD = outputD | totalWeight;
		
		PORTD = outputD; //first two bits represent the conditions, bits 7-1 represent the approx weight of all riders(multiply by 64 to get weight in kgs).
	}
}

