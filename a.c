#include <stdio.h>
#include <msp430.h>

int main(void) {
	WDTCTL  = WDTPW | WDTHOLD; // Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;     // Run @ 1MHz
	DCOCTL  = CALDCO_1MHZ;

    int i = 0;

    while (1) { // Keep the program running
        //print_something();

        int segments = 0b1111111; // this will change the segments that light up on the current "frame" or loop iteration

        light_segments(segments);

        int digits = 0b0000;
        disable_digits();

        if(i == 0) {
            digits |= BIT0;
        }
        if(i == 1) {
            digits |= BIT1;
        }
        if(i == 2) {
            digits |= BIT4;
        }
        if(i == 3) {
            digits |= BIT7;
        }

        enable_digits(digits);

        //__delay_cycles(150000);

        if(i >= 3) {
            i = 0;
        } else {
            i++;
        }


    }
}

void enable_digits(int d) {
    // setting the digits we want to be displayed as outputs
    P3DIR |= d; 

    // turning off the bits for which digits we want shown
    P3OUT &= ~(d);
}

void light_segments(int s) {
    // enabling all possible segments as outputs (this also turns on the segments)
    P2SEL &= ~(BIT6 | BIT7);
    P2SEL2 &= ~(BIT6 | BIT7);

    // BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6
    P2DIR |= (s);
    P2OUT |= (s); // turns off bit segment c
}

void disable_digits() {
    P3DIR |= BIT0 | BIT1 | BIT4 | BIT7;
    P3OUT |= BIT0 | BIT1 | BIT4 | BIT7;
}
