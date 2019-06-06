/*
 * File:   main.c
 * Author: Usr
 *
 * Created on 14 dicembre 2018, 15.33
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

void main(void) {
    //porta b = uscita
    TRISB = 0x00;
    
    while(1)
    {
        int i;
        
        for(i=0;i<8;i++){
            PORTB = 0x01 << i;
            __delay_ms(200);
        }
        for(i=0;i<8;i++){
            PORTB = 0x80 >> i;
            __delay_ms(200);
        }
        /*
        PORTB = 0x02;
        __delay_ms(500);
        PORTB = 0x00;
        __delay_ms(500);
         * */
    }
    return;
}
