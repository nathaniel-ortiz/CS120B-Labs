#include <avr/io.h>

int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputC = 0x00;
	
	while(1) {
		
		inputA = PINA;
		
		if((inputA & 0x0F) == 0x00) {
			outputC = 0x40;
		}
		
		else if((inputA & 0x0F) == 0x01 || (inputA & 0x0F) == 0x02) {
			outputC = 0x60;
		}
		
		else if((inputA & 0x0F)== 0x03 || (inputA & 0x0F) == 0x04) {
			outputC = 0x70;
		}
		
		else if((inputA & 0x0F) == 0x05 || (inputA & 0x0F) == 0x06) {
			outputC = 0x38;
		}
		
		else if((inputA & 0x0F) == 0x07 || (inputA & 0x0F) == 0x08 || (inputA & 0x0F) == 0x09) {
			outputC = 0x3C;
		}
		
		else if((inputA & 0x0F) == 0x0A || (inputA & 0x0F) == 0x0B || (inputA & 0x0F) == 0x0C) {
			outputC = 0x03E;
		}
		
		else if((inputA & 0x0F) == 0x0D || (inputA & 0x0F) == 0x0E || (inputA & 0x0F) == 0x0F) {
			outputC = 0x3F;
		}
		
		if((inputA & 0xF0) == 0x30) {
			outputC = outputC | 0x80;
		}
		
		PORTC = outputC;
	}
}