#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void threeLED(unsigned char output, unsigned char currLED) {
	if(currLED == 0) {
		output = output & 0x09;
		currLED++;
	}
	else if(currLED == 1) {
		output = output & 0x0A;
		currLED++;
	}
	else if(currLED == 2) {
		output = output & 0x0C;
		currLED = 0;
	}
}

void blinkLED(unsigned char output) {
	if((output & 0x08) == 0x08) {
		output = output & 0xF7;
	}
	else {
		output = output | 0x08;
	}
}

void pulseSpeaker(unsigned char output) {
	if((output & 0x10) == 0x10) {
		output = output & 0x0F;
	}
	else {
		output = output | 0x10;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char output = 0x00;
	unsigned char currLED = 0x00;
	unsigned char inputA = 0x00;
	unsigned int threeLED_time = 300;
	unsigned int blinkLED_time = 1000;
	unsigned int pulseSpeaker_time = 0;
	TimerSet(1);
	TimerOn();
	while (1)
	{
		if(threeLED_time >= 300) {
			if(currLED == 0) {
				output = output & 0x08;
				
				output = output | 0x01;
				currLED++;
			}
			else if(currLED == 1) {
				output = output & 0x08;
				output = output | 0x02;
				currLED++;
			}
			else if(currLED == 2) {
				output = output & 0x08;
				output = output | 0x04;
				currLED = 0;
			}
			threeLED_time = 0;
		}
		if(blinkLED_time >= 1000) {
			if((output & 0x08) == 0x08) {
				output = output & 0xF7;
			}
			else {
				output = output | 0x08;
			}
			blinkLED_time = 0;
		}
		if(~PINA == 0x01) { 
			if(pulseSpeaker_time >= 2) {
				output = output ^ 0x10;
				pulseSpeaker_time = 0;
			}
		}
		PORTB = output;
		while(!TimerFlag);
		TimerFlag = 0;
		threeLED_time++;
		blinkLED_time++;
		pulseSpeaker_time++;
	}
}