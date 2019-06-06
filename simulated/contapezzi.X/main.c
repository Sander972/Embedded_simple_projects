/*
 * File:   main.c
 * Author: Ale
 *
 * Created on 24 gennaio 2019, 15.19
 */
// PIC16F628A Configuration Bit Settings
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 8000000      // Frequenza del sistema. E' obbligatoria

#include <xc.h>

int disp=0;
int flag=0;
int tempo=0;
int d =0; //decine
int u =0; //unita'
int count=0;
int num=0;
bit old_press=0;
char state=0;
char old_state=0;



void write(int d, int u)
{
    
    char segment[10] = {
        
        //dispDX
        0b11111110, // 0
        0b00111000, // 1
        0b11011101, // 2
        0b01111101, // 3
        0b00111011, // 4
        0b01110111, // 5
        0b11110111, // 6
        0b00111100, // 7
        0b11111111, // 8
        0b01111111, // 9

        /*
        0b10101111, // A
        0b11100011, // B
        0b11000110, // C
        0b11101001, // D
        0b11000111, // E
        0b10000111  // F
        */
    };
   
    if(disp){
        PORTB = segment[d] | 0x10;
    }else{
        PORTB = segment[u];
    }
    
}

void init()
{
    TRISA = 0x02;
    TRISB = 0x00; 
    INTCON = 0xE0;
    OPTION_REG = 0x02;
}

void check_button()
{
    if((!(PORTA & 0x02)) && (old_press))
    {
        // Se sto premendo il pulsante e l'ho premuto in precedenza
        old_press = 0;
        state = state ^ 0xFF;
    }
    if((PORTA & 0x02) && (!old_press))
    {
        // Se sto premendo il pulsante e non l'ho premuto in precedenza
        __delay_ms(50);
        if((PORTA & 0x02) && (!old_press))
        {
            old_press = 1;
        }
    }
    
}

void main(void) {
    
    init();
    while(1)
    {
        
        if(flag){
            check_button();
            count++;
            if(count>1000){
                tempo++;
                count=0;
            }
            
            if(state != old_state){
                num++;
                d =(num/10);   //decine
                u =(num%10);   //unita'
                write(d,u);
                if(num>98){
                    num=0;
                }
                old_state = state;
            }
            
            if(!(PORTA & 0x02)){
                
            }
            if(tempo == 60){
                tempo =0;
                num=0;
                d =(num/10);   //decine
                u =(num%10);   //unita'
                write(d,u);
            }
            flag=!flag;
        }
        
    }
    
    return;
}


void interrupt ISR()
{
    if(T0IF)
    {
        T0IF=0;
        TMR0 = 6;
        disp=!disp;
        flag=1;
    }
    return;
}

