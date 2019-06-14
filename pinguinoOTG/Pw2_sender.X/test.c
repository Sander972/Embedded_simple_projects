Matteo Ict, [13.06.19 17:24]
/*
 * File:   main.c
 * Author: Utente
 *
 * Created on 7 giugno 2019, 15.37
 */
#pragma config FPLLIDIV = DIV_2 // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20 // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2 // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1 // System PLL Output Clock Divider (PLL Divide by 256)
// DEVCFG1
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8 // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
// DEVCFG0
#pragma config DEBUG = OFF // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF // Program Flash Write Protect (Disable)
#pragma config BWP = OFF // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF

#include <p32xxxx.h>
#include <plib.h>

#define SYSCLK 80000000
#define BAUD_VALUE 9600

void initializeUART(){
// Optimize PIC32 performance and return peripheral bus frequency
double pbClk=SYSTEMConfig( SYSCLK, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
// Abilita UART1 and set baud rate to DESIRED_BAUDRATE=9600
OpenUART1( UART_EN, UART_RX_ENABLE | UART_TX_ENABLE, pbClk/16/BAUD_VALUE-1);
while( BusyUART1()); // Attendo che il modulo UART sia libero
}

void delay(int t){
    int n = t*1900;
    while (n > 0) {n--;}
}

void main(void) {
   
    OpenUART1(UART_EN, UART_RX_ENABLE | UART_TX_ENABLE, 9600); // da controllare se mettere già qua il valore
// Configure UART1 RX Interrupt
    ConfigIntUART1(UART_INT_PR2 | UART_RX_INT_EN);
// Must enable glocal interrupts - in this case, we are using multi-vector mode
    INTEnableSystemMultiVectoredInt();
   
   
   
    char datoLedUp[8] = {0,1,1,0,0,0,0,1};
    char datoLedDown[8] = {0,1,1,1,1,0,1,0};
    //char datoLedUp = 'a';
    while(1){
        /*
        //while(BusyUART1());
        for(int i=0;i<8;i++)
        {
            putcUART1 (datoLedUp[i]);
        } */      
          putcUART1('a');
         
       
        delay(1000);
       
         putcUART1('z');
        /*
        for(int i=0;i<8;i++)
        {
            putcUART1(datoLedDown);
        }
        delay(1000);
       
        while(BusyUART1());
        putcUART1(datoLedDown);*/
    }
    return;
}