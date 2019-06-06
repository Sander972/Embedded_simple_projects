/*
 * File:   main.c
 * Author: Usr
 *
 * Created on 20 dicembre 2018, 11.41
 */
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define _XTAL_FREQ 8000000

#include <xc.h>

#define num 2

void main(void) {

    TRISA = 0xFF;
    TRISB = 0x00;

    const char sequenza[num][10] = {
        {0x01, 0x03, 0x05, 0x09, 0xa0, 0xa4, 0xa2, 0xc3, 0xc7, 0xf1},
        {0x02, 0x06, 0xf3, 0xaa, 0xb4, 0xc2, 0xd6, 0xe9, 0xf1, 0x6a}
    };
    static bit a = 0, b = 0;
    char f = 0;
    char c = 0;

    while (1) {
        c = !(PORTA & 0x02);
        if (c && b) {
            a = !a;
            f++;
            __delay_ms(20);
        }
        if (a) {
            int i;
            for (i = 0; i < 10; i++) {
                PORTB = sequenza[f][i];
                //contatore(500);
                __delay_ms(500);
            }

        }

        b = !a;
        if (f > (num - 1)) f = 0;

    }


    return;
}

/*
void contatore(int ms){       
    int i;
    for(i=0;i<ms;i++){
        __delay_ms(1);
    }
}
 */