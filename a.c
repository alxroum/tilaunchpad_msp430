#include <stdio.h>
#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

int main(void) {
	WDTCTL  = WDTPW | WDTHOLD; // Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;     // Run @ 1MHz
	DCOCTL  = CALDCO_1MHZ;

    scramble();
    //method2();

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

void disable_segments() { // turn off any lingering bits so that they are not left displayed as segments

    P2SEL &= ~(BIT6 | BIT7);
    P2SEL2 &= ~(BIT6 | BIT7);

    // BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6
    P2DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6);
    P2OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6); // turns off bit segment c
}

int number_to_segments(int n) {

    if(n > 9) {
        n = n - 10;
    }

    if(n == 0) {
        return 0b0111111;
    }
    if(n == 1) {
        return 0b0110000;
    }
    if(n == 2) {
        return 0b1011011;
    }
    if(n == 3) {
        return 0b1111001;
    }
    if(n == 4) {
        return 0b1110100;
    }
    if(n == 5) {
        return 0b1101101;
    }
    if(n == 6) {
        return 0b1101111;
    }
    if(n == 7) {
        return 0b0111000;
    }
    if(n == 8) {
        return 0b1111111;
    }
    if(n == 9) {
        return 0b1111101;
    }
}

void scramble() {

    int i = 0;
    int timeDelay = 0;
    int displayVal = 0;
    int timeBeforeSwitch = 35; // time delay before numbers update
    int segments = 0b0000000; // this will change the segments that light up on the current "frame" or loop iteration

    while (1) { // Keep the program running
        //print_something();

        //segments = 0b0000000;
        
        if(timeDelay > timeBeforeSwitch) {
            timeDelay = 0;
            displayVal++;
        } else {
            timeDelay++;
        }

        if(displayVal > 9) {
            displayVal = 0;
        } 

        int digits = 0b0000;
        disable_digits();
        disable_segments();

        if(i == 0) {
            digits |= BIT0;
            segments = number_to_segments(displayVal); // segments to be lit at digit 0
        }
        if(i == 1) {
            digits |= BIT1;
            segments = number_to_segments(displayVal + 1);
        }
        if(i == 2) {
            digits |= BIT4;
            segments = number_to_segments(displayVal + 2);
        }
        if(i == 3) {
            digits |= BIT7;
            segments = number_to_segments(displayVal + 3);
        }

        enable_digits(digits);

        light_segments(segments);

        __delay_cycles(1500); // 1500 is a good speed

        if(i >= 3) {
            i = 0;
        } else {
            i++;
        }
    }
}
/*
void method2() {

    int i = 0;
    int segments = 0b0000000; // this will change the segments that light up on the current "frame" or loop iteration

    serial_init(9600);

    configureADC10();

    while (1) { // Keep the program running

        P1DIR &= ~BIT4;
        //P1OUT |= BIT4;

        cio_printf("%d, %d\n\r", P1DIR, readADC());
        
        

        __delay_cycles(150000);
    }
}

void configureADC10() {
    ADC10CTL1 = INCH_4;
    ADC10CTL0 = SREF_0 | ADC10SHT_2 | ADC10ON;
    ADC10AE0 |= BIT4;
}

unsigned int readADC() {
    ADC10CTL0 |= ENC | ADC10SC;
    while(ADC10CTL1 & ADC10BUSY);
    return ADC10MEM;
} */
