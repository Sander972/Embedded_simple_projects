/*
 * File:   main.c
 * Author: Minca Alessandro
 *
 * Created on 25 gennaio 2019, 14.20
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

#define _XTAL_FREQ 40000000     //40 MHz    

#include <xc.h>

/*
 check-list:
 * visualizzare i numeri sul disp               ok
 * conto alla rovesci fisso (no button)         ok
 * conto alla rovescia con button               ok
 * scritta of                                   circa --> lampeggia ogni sec e non mezzo sec
 * modifica conto alla rovescia                 no  (funzioni ci sono ma non vanno)
 * accensione RA1 e RA2 e RA3                   no (esempio di implementazione)
 * 
 
 */

/*
 funzionamento:
 * ra1 fa da start/stop
 * ra2 dovrebbe incremetare timp(tempo impostato)
 * ra2 dovrebbe diminuire timp(tempo impostato)
 * 
 */

int disp=0;
int flag=0;
int tempo=60;   
int d =0; //decine
int u =0; //unita'
int count=0;
int gigi=0;
int timp = 60;      //tempo impostato
int old_press=0;
bit state=0;
bit old_state=0;
int dec;
int start=0;
int f=0;
int pippo=0;

bit s1=0;
bit s2=0;
bit s3=0;

void write(int d, int u);
void check_button();

const char segment[10] = {      //mi definisco le posizioni del 7 segmenti
        0b11101110, // 0
        0b00101000, // 1
        0b11001101, // 2
        0b01101101, // 3
        0b00101011, // 4
        0b01100111, // 5
        0b11100111, // 6
        0b00101100, // 7
        0b11101111, // 8
        0b01101111, // 9
    };


void init(){

    
    TRISB = 0x00; 
    INTCON = 0xE0;
    OPTION_REG = 0x05;
    
}


void write(int d, int u)
{
    
    if(disp){
        if(d=='o'){
            PORTB = 0b11101110; //0
        }else{PORTB = segment[d];}
    }else{
        if(u=='f'){
            PORTB = 0b10010111;  //f
        }else{PORTB = segment[u] | 0x10;}

    }
    
}

void off(){         //mantengo il tempo a 0 per 5 sec così posso far lampeggiare "of"
  gigi++;
  tempo=0;
  if(gigi>4){
    tempo=60;       //ripristino il conto alla rovesci al valore di default
    start=0;
    gigi=0;
    d =(tempo/10);   //decine
    u =(tempo%10);   //unita'
  }
    
}

void led(){                     //funzione per controllare ra1, ra2, ra3 sempio di implementazione
    if(tempo>(timp/2)){
        //PORTB = 0x00;           //accendo ra1
                                //spengo ra2
                                //spengo ra3
    }else{
                                //accendo ra1
                                //accendo ra2
                                //spengo ra3
        if(tempo<30){
                                //accendo ra1, ra2, ra3
        }
    }
    

}

void main(void) {
    
    init();
    d =(tempo/10);   //decine
    u =(tempo%10);   //unita'
    while(1)
    {   
        check_button();
        if(flag){           //da interrupt
            if(start){      //finchè non premo s1 non parte il conto alla rovescia
                count++;
            }
            if(start>1){    //se premo di nuovo s1 tempo va a zero
                tempo=0;
            }
            if(count>945){  //ogni circa 1000ms passa 1 sec
                if(tempo == 0){     //
                    off();
                }else{
                    tempo = tempo - 1;
                    d =(tempo/10);   //decine
                    u =(tempo%10);   //unita'
                    //write(d,u);
                }
                count=0;
            }
            flag=!flag;
        }
        if(tempo!=0){
            write(d,u);
            //led();        //quando funziona la riattivo
        }
        else{
            if((gigi%2)==0){
                write('o','f');
            }else{
                PORTB = 0x00;
            }
            
        }
        
    }
    return;
}


void interrupt ISR()
{
    if(T0IF)
    {
        T0IF=0;
        TMR0 = 100;
        disp=!disp;
        flag=1;
    }
    return;
}

int check(char num)
{
    TRISA = 0xFF;
    if((!(PORTA & num)) && (old_press))
    {
        // Se sto premendo il pulsante e l'ho premuto in precedenza
        old_press = 0;
        state = state ^ 0xFF;
    }
    if((PORTA & num) && (!old_press))
    {
        // Se sto premendo il pulsante e non l'ho premuto in precedenza
        __delay_ms(50);
        if((PORTA & 0x02) && (!old_press))
        {
            old_press = 1;
        }
    }
    if(state != old_state)
    {
        old_state = state;
        f++;
    }else{f=0;}
    
    return f;
}

void check_button(){
    for(int i=0;i<3;i++){
        pippo = check(0x02 << i);
        if(pippo){
            switch(i){
            case 0:     //ra1
                //s1=!s1;
                start++;
                tempo = timp;
            case 1:     //ra2
                //s2=!s2;
                timp++;
            case 2:     //ra3
                //s2=!s2;
                timp--;
                
        
        }
        }
        
    }

}

