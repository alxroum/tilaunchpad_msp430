#include <msp430.h>

int main(void) {
	WDTCTL  = WDTPW | WDTHOLD; // Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;     // Run @ 1MHz
	DCOCTL  = CALDCO_1MHZ;

	

	P2DIR |= BIT0; // enabling output on pin 2.0
	P2DIR |= BIT1; // pin 2.1
	P2DIR |= BIT2;
	P2DIR |= BIT3;
	P2DIR |= BIT4;
	P2DIR |= BIT5;
	P2DIR |= BIT6; // pin 2.6


	//bit1 turns on          u5
	//bit4 turns on      u4
	//~bit1 turns on u3, u4
	//~bit2 turns on u3, u4, u5
	//~bit4 turns on u3,     u5

	P3DIR |= ~BITC; // this determines how many numbers are displayed somehow 


	P2OUT |= BIT0;
	P2OUT |= BIT1;
	P2OUT |= BIT2;
	P2OUT |= BIT3;
	P2OUT |= BIT4;
	P2OUT |= BIT5;
	P2OUT |= BIT6;
	//P3OUT = BIT0;
}