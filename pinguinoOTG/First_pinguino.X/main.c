/*
 * File:   main.c
 * Author: Sander
 *
 * Created on 8 maggio 2019, 17.10
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
#pragma config CP = OFF // Code Protect (Protection Disabled)
#include <p32xxxx.h>
#include <plib.h> // Include the PIC32 Peripheral Library.

#define SYSCLK 80000000L // Give the system?s clock frequency

const char car[14] = {
        0x0004,
        0x0008,
        0x0011,
        0x0020,
        0x0040,
        0x0080,
        0x0100,
        0x0800,
        0x0100,
        0x0080,
        0x0040,
        0x0020,
        0x0011,
        0x0008
                   
    };

int i = 0;
int t =1000;
int prev =0;

int main(void)
{
    SYSTEMConfigPerformance(SYSCLK);
    TRISD = 0x0000;
    OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_256, 0xFFFF);
    ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2);
    INTEnableSystemMultiVectoredInt();
    
    //TRISD = 0x0011; // imposto RD4 come ingresso e il resto come uscita
    while( 1)
    {
        //LATDbits.LATD1 = !PORTDbits.RD4;
        PORTDbits.RD4 = car[i];
        if(tmr1()){
            change();
        }
    }
    return 1;
}


void change()
{
    if(tmr1)
    {
        if(i<14){
            i++;
        }else{
            i = 0;
        }
    }
    return;
}


int tmr1(){
    int now = ReadTimer2();
    if(now-prev >t){
        return 1;
    }else{
        return 0;
    }
    prev = now;
}