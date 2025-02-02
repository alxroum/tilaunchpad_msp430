#include <msp430.h>

int main(void) {
	WDTCTL  = WDTPW | WDTHOLD; // Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;     // Run @ 1MHz
	DCOCTL  = CALDCO_1MHZ;


    light_segments();

    enable_digits();

    while (1); // Keep the program running
}

void enable_digits() {
    // setting the digits we want to be displayed as outputs
    P3DIR |= BIT0 | BIT1 | BIT4 | BIT7; 

    // turning on the bits for which digits we want shown
    P3OUT &= (~BIT0 | ~BIT1 | ~BIT4 | ~BIT7);
    // doing operation again to flip from off to on
    P3OUT &= ~(BIT0 | BIT1 | BIT4 | BIT7);
}

void light_segments() {
    // enabling all possible segments as outputs (this also turns on the segments)
	P2DIR |= BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5; // set pin 2.0-2.6 as an output
}