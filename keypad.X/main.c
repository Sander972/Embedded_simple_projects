/*
 * File:   main.c
 * Author: Ale
 *
 * Created on 24 gennaio 2019, 15.37
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 8000000
#include <xc.h>

void main(void) {
    unsigned char colScan=0;
    unsigned char rowScan=0;
    unsigned char keypressed=0;
    char keyok;
    TRISB = 0x00;
    TRISD = 0x0F;
    const unsigned char colMask[3] =
    {
        0b11111110, // Colonna 1 => RB0 a massa
        0b11111101, // Colonna 2 => RB1 a massa
        0b11111011 // Colonna 3 => RB2 a massa
    };
    const unsigned char rowMask[4] =
    {
        0b00000001, // Riga 1
        0b00000010, // Riga 2
        0b00000100, // Riga 3
        0b00001000 // Riga 4
    };
    const unsigned char keys[] =
    {
        0b00001010, //0  #
        0b00000111, //1  7
        0b00000100, //2  4
        0b00000001, //3  1
        0b00000000, //4  0
        0b00001000, //5  8
        0b00000101, //6  5
        0b00000010, //7  2
        0b00001011, //8  *
        0b00001001, //9  9
        0b00000110, //10 6
        0b00000011  //11 3
    };

    // porto a massa una colonna alla volta
    for (colScan = 0; colScan < 3; colScan++)
    {
       PORTB = PORTB | 0x07; // porto tutte le colonne a 1
       PORTB &= colMask[colScan]; // porto a zero la colonna attuale
       for (rowScan=0; rowScan<4; rowScan++)
       {
          if (!(PORTD & rowMask[rowScan])) // Riga rowScan trovata a massa
          {
            __delay_ms(5);
            // versione con delay, si pu? migliorare
            // rendendolo sensibile al fronte
            if (!(PORTD & rowMask[rowScan]))
            {
               keypressed=rowScan+(4*colScan); // numero di pulsante premuto
               keyok=1; // E? stato premuto un pulsante
            }
           }
       }
       
        if (keyok)
        {
           // vorrei rappresentare il tasto premuto sui 4 bit
           // piu' significativi di PORTD
           PORTD = PORTD & 0x0F;
           PORTD = PORTD | (keys[keypressed] << 4);
           keyok=0; // resetto il flag di pulsante premuto
           // rimango in un ciclo continuo fino a che
           // il pulsante non viene rilasciato
           PORTB=PORTB | 0x07;
           while((PORTB & 0x07) != 0x07)
           {
              continue;
           }
        }
    }
    return;
}
