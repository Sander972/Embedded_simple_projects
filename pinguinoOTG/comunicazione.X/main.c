/*
 * File:   main.c
 * Author: Usr
 *
 * Created on 31 maggio 2019, 15.31
 */

#pragma config FPLLIDIV = DIV_2 // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20 // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2 // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1 // System PLL Output Clock Divider (PLL Divide by 256)
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8 // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config DEBUG = OFF // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF // Program Flash Write Protect (Disable)
#pragma config BWP = OFF // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF // Code Protect (Protection Disabled)
#include <p32xxxx.h>
#include <plib.h> // Include the PIC32 Peripheral Library.

#define SYSCLK 80000000L // Give the system?s clock frequency
#include <xc.h>

/*
char flag = 0;

void checkTmr() {
    if (ReadTimer1() / 100) {
        flag = !flag;
    }
}

int sveglia(int time) {
    char finish;
    char t = 0;
    if (flag) {
        if (t < time) {
            t++;
            finish = 0;
        } else {
            finish = 1;
            t = 0;
        };
    };
    return finish;
}
*/

void delay (int t)
{
    int n = t*1900; //1900 è un numero ricavato sperimentalmente
    while(n>0) {n--;}
}

void main(void) {

    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, 0xFFFF);     //0xAFC     0xFFFFFFFF
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2);
    INTEnableSystemMultiVectoredInt();

    TRISD = 0x0000;
    //LATD = 0x0000;
    //LATDbits.LATD2 = 0;

    while (1) {
        //checkTmr();

        //LATDbits.LATD2 = flag;

        //if(!sveglia(10)){ LATD = 0x0080;}
        //LATDbits.LATD2 = 0;
        //LATD = 0x0004;
        //LATDbits.LATD2 = 1;
        //delay(10);
        //LATDbits.LATD2 = 0;
        //delay(10);

    }
    return;
}

void __ISR(_TIMER_1_VECTOR, ipl2) handlesTimer1Ints(void) {

    LATDbits.LATD2 = ~LATDbits.LATD2;
    mT1ClearIntFlag();

}
