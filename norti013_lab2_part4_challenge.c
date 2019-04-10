/*	Partner 1 Name & E-mail: Nathaniel Ortiz norti013@ucr.edu
 *	Lab Section: 028
 *	Assignment: Lab 2  Exercise 4	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char inputA = 0x00;
	unsigned char outputB = 0x00;
	unsigned char outputC = 0x00;
	
	//read from portA, write upper 4 bits of A and write to B, take lower four bits of A, and write to upper four bits of C
	
	while(1) {
		
		inputA = PINA;
		
		outputB = inputA & 0x0F;
		outputB = outputB << 4;
		outputC = inputA & 0xF0;
		outputC = outputC >> 4;
		
		
	}
}