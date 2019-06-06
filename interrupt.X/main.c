/*
 * File:   main.c
 * Author: Usr
 *
 * Created on 21 dicembre 2018, 14.54
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

static bit led;
int count = 0;

void main(void) {
    TRISB = 0x00;
    INTCON = 0xE0; //GIE = 1; PEIE = 1; TMR0IE = 1;
    OPTION_REG = 0x07; //PS0 = 1; PS1 = 1; PS2 = 1;
    //PORTB = 0xAA;
    PORTB = 0x01;
    while (1) {
        
    }
    return;
}

void interrupt ISR() {
    if (INTCON & 0x04) {
        INTCON &= ~0x04; // ~0x04 è la negazione di 0x04 ? 0xFB
        count++;
        if (count == 30) {
            PORTBbits.RB0 = !PORTBbits.RB0;
            //PORTB = ~PORTB; // nego il valore di tutti i bit di PORTB
            count = 0;
        }
        
    }
    return;
}