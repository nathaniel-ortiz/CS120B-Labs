#include <avr/io.h>
#include <avr/interrupt.h>
#include "ucr/bit.h"
#include "ucr/timer.h"
#include <stdio.h>
#include "ucr/io.c"
#include "ucr/io.h"

unsigned char GetKeypadKey() {

	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('1'); }
	if (GetBit(PINC,1)==0) { return('4'); }
	if (GetBit(PINC,2)==0) { return('7'); }
	if (GetBit(PINC,3)==0) { return('*'); }

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('2'); }
	if (GetBit(PINC,1)==0) { return('5'); }
	if (GetBit(PINC,2)==0) { return('8'); }
	if (GetBit(PINC,3)==0) { return('0'); }

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('3'); }
	if (GetBit(PINC,1)==0) { return('6'); }
	if (GetBit(PINC,2)==0) { return('9'); }
	if (GetBit(PINC,3)==0) { return('#'); }

	// Check keys in col 4
	PORTC = 0x7F;
	asm("nop");
	if (GetBit(PINC,0)==0) { return('A'); }
	if (GetBit(PINC,1)==0) { return('B'); }
	if (GetBit(PINC,2)==0) { return('C'); }
	if (GetBit(PINC,3)==0) { return('D'); }

	return('\0'); // default value

}

//--------Find GCD function --------------------------------------------------
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
b = c;
	}
	return 0;
}
//--------End find GCD function ----------------------------------------------

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;

//--------End Task scheduler data structure-----------------------------------

//--------Shared Variables----------------------------------------------------
unsigned char SM2_output = 0x00;
unsigned char SM3_output = 0x00;
unsigned char pause = 0;

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
const unsigned char phrase[67]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

enum SM1_States{SM1_output};
unsigned char cursor = 1;


int SMTick1(int state){
	switch(state){
		case SM1_output:
		for(int j = 1; j <= 16; j++){
			LCD_Cursor(j);
			LCD_WriteData(phrase[cursor + j - 2]);
			if(cursor + j + 1 == 69){
				cursor = 1;
			}
			
		}
		cursor++;
		
	}
	return state;
}

//Enumeration of states.
enum SM2_States { SM2_wait, SM2_blink };

// If paused: Do NOT toggle LED connected to PB0
// If unpaused: toggle LED connected to PB0
int SMTick2(int state) {

	LCD_init();
	//State machine transitions
	switch (state) {
	case SM2_wait:	if (pause == 0) {	// If unpaused, go to blink state
		state = SM2_blink;
	}
	break;

	case SM2_blink:	if (pause == 1) {	// If paused, go to wait state
		state = SM2_wait;
	}
	break;

	default:		
		state = SM2_wait;
		break;
	}

	//State machine actions
	switch(state) {
	case SM2_wait:	
	LCD_DisplayString(1, "CS120B is Legend");
	delay_ms(250);
	LCD_ClearScreen();
	LCD_DisplayString(1, "S120B is Legend.");
	delay_ms(250);
	LCD_ClearScreen();
	LCD_DisplayString(1, "120B is Legend..");
	delay_ms(250);
	LCD_ClearScreen();
	LCD_DisplayString(1, "20B is Legend...");
	break;

	case SM2_blink:
	delay_ms(250);
	LCD_ClearScreen();
	LCD_DisplayString(1, "...DARY!");
	break;

	default:		break;
	}

	return state;
}

//Enumeration of states.
enum SM3_States { SM3_wait, SM3_blink };

// If paused: Do NOT toggle LED connected to PB1
// If unpaused: toggle LED connected to PB1
int SMTick3(int state) {
	//State machine transitions
	switch (state) {
	case SM3_wait:	if (pause == 0) {	// If unpaused, go to blink state
state = SM3_blink;
}
break;

	case SM3_blink:	if (pause == 1) {	// If paused, go to wait state
state = SM3_wait;
}
break;

	default:		state = SM3_wait;
				break;
	}

	//State machine actions
	switch(state) {
	case SM3_wait:	break;

	case SM3_blink:	SM3_output = (SM3_output == 0x00) ? 0x02 : 0x00; //toggle LED
				break;

	default:		break;
	}

	return state;
}


//Enumeration of states.
enum SM4_States { SM4_display };

// Combine blinking LED outputs from SM2 and SM3, and output on PORTB
int SMTick4(int state) {
	// Local Variables

	unsigned char output;

	//State machine transitions
	switch (state) {
	case SM4_display:	break;

	default:		state = SM4_display;
				break;
	}

	//State machine actions
	switch(state) {
	case SM4_display:	output = SM2_output | SM3_output; // write shared outputs
									// to local variables
break;

	default:		break;
	}

	PORTB = output;	// Write combined, shared output variables to PORTB

	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
// Set Data Direction Registers
// Buttons PORTA[0-7], set AVR PORTA to pull down logic
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTA = 0x00;
	LCD_init();
// . . . etc

// Period for the tasks
unsigned long int SMTick1_calc = 200;
//unsigned long int SMTick2_calc = 500;
//unsigned long int SMTick3_calc = 1000;
//unsigned long int SMTick4_calc = 10;

//Calculating GCD
unsigned long int tmpGCD = SMTick1_calc;
//tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
//tmpGCD = findGCD(tmpGCD, SMTick3_calc);
//tmpGCD = findGCD(tmpGCD, SMTick4_calc);

//Greatest common divisor for all tasks or smallest time unit for tasks.
unsigned long int GCD = tmpGCD;

//Recalculate GCD periods for scheduler
unsigned long int SMTick1_period = SMTick1_calc;
//unsigned long int SMTick2_period = SMTick2_calc/GCD;
//unsigned long int SMTick3_period = SMTick3_calc/GCD;
//unsigned long int SMTick4_period = SMTick4_calc/GCD;

//Declare an array of tasks 
//static task task1, task2, task3, task4;
static task task1;
//task *tasks[] = { &task1, &task2, &task3, &task4 };
task *tasks[] = { &task1 };
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

// Task 1
task1.state = 0;//Task initial state.
task1.period = SMTick1_period;//Task Period.
task1.elapsedTime = SMTick1_period;//Task current elapsed time.
task1.TickFct = &SMTick1;//Function pointer for the tick.

/*// Task 2
task2.state = -1;//Task initial state.
task2.period = SMTick2_period;//Task Period.
task2.elapsedTime = SMTick2_period;//Task current elapsed time.
task2.TickFct = &SMTick2;//Function pointer for the tick.*/

/*// Task 3
task3.state = -1;//Task initial state.
task3.period = SMTick3_period;//Task Period.
task3.elapsedTime = SMTick3_period; // Task current elasped time.
task3.TickFct = &SMTick3; // Function pointer for the tick.

// Task 4
task4.state = -1;//Task initial state.
task4.period = SMTick4_period;//Task Period.
task4.elapsedTime = SMTick4_period; // Task current elasped time.
task4.TickFct = &SMTick4; // Function pointer for the tick.*/

// Set the timer and turn it on
TimerSet(GCD);
TimerOn();

//Clear LCD
	LCD_init();
	LCD_ClearScreen();

unsigned short i; // Scheduler for-loop iterator
while(1) {
	// Scheduler code
	for ( i = 0; i < numTasks; i++ ) {
		// Task is ready to tick
		if ( tasks[i]->elapsedTime == tasks[i]->period ) {
			// Setting next state for task
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			// Reset the elapsed time for next tick.
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 1;
	}
	while(!TimerFlag);
	TimerFlag = 0;
}

// Error: Program should not exit!
return 0;
}
