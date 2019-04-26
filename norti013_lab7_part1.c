#include <avr/io.h>
#include "io.c"

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	unsigned char state = 0;
	unsigned char number = 0;
	unsigned char inputA = 0x00;
	
	// Initializes the LCD display
	LCD_init();
	
	while(1) {
		switch(state) {
			case 0:
				LCD_WriteData('0');
				state = 1;
				break;
			case 1:
				inputA = ~PINA;
				if(inputA == 0x00) {
					state = 1;
				}
				else if(inputA == 0x01) {
					state = 2;
				}
				else if(inputA == 0x02) {
					state = 3;
				}
				else if(inputA == 0b00000011) {
					state = 5;
				}
				else {
					state = 255;
				}
				break;
			case 2:
				if(number != 9) {
					number++;
					LCD_ClearScreen();
					LCD_WriteData(number + '0');
					state = 4;
				}
				else {
					state = 1;
					
				}
				break;
			case 3:
				if(number != 0) {
					number--;
					LCD_ClearScreen();
					LCD_WriteData(number + '0');
					state = 4;
				}
				else {
					state = 1;
				}
				break;
			case 4:
				while(PINA != 0xFF) {
					state = 4;
				}
				state = 1;
				break;
			case 5:
				LCD_ClearScreen();
				LCD_WriteData('0');
				state = 4;
				break;
			default:
				LCD_WriteData("Invalid input");
				break;
		}	
	}
}