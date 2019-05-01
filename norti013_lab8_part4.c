#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}



int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0x00; PORTA = 0xFF;

	ADC_init();
	while(1)
	{
		unsigned short analogVal = ADC;
		
		if(analogVal < 768/8) {
			PORTB = 0x01;
		}
		else if(analogVal > 768/8 && analogVal < (2*(768/8))) {
			PORTB = 0x03;
		}
		else if(analogVal > (2*(768/8)) && analogVal < (3*(768/8))) {
			PORTB = 0x07;
		}
		else if(analogVal > (3*(768/8)) && analogVal < (4*(768/8))) {
			PORTB = 0x0F;
		}
		else if(analogVal > (4*(768/8)) && analogVal < (5*(768/8))) {
			PORTB = 0x1F;
		}
		else if(analogVal > (5*(768/8)) && analogVal < (6*(768/8))) {
			PORTB = 0x3F;
		}
		else if(analogVal > (6*(768/8)) && analogVal < (7*(768/8))) {
			PORTB = 0x7F;
		}
		else {
			PORTB = 0xFF;
		}
	}
}
