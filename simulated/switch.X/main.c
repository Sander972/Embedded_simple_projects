/*
 * File:   main.c
 * Author: Usr
 *
 * Created on 20 dicembre 2018, 9.50
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
    
    TRISA = 0xFF;   
    TRISB = 0x00;
    
    static bit a = 0, b = 0;
    char c;
    while(1){
        c = !(PORTA&0x02);
        if(c && b){
            //a = a ^ 1;
            a =! a;
            __delay_ms(20);  
    }
    if(a)PORTB = 0x01;
    else PORTB = 0x00;
    b = !a;
   
           
        
             
            
        //__delay_ms(150);
        
    
    }
    
    
    
    return;
}
