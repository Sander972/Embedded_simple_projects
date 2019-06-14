/*
 * File:   main.c
 * Author: Usr
 *
 * Created on 13 giugno 2019, 16.39
 */


/*SENDER*/
/*
tested 13/6/2019 --> working
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
#include <plib.h>

#define SYSCLK 8000000 
#define DESIRED_BAUDRATE 9600

void initializeUART() {
    // Optimize PIC32 performance and return peripheral bus frequency
    double pbClk = SYSTEMConfig(SYSCLK, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    // Abilita UART1 and set baud rate to DESIRED_BAUDRATE=9600
    OpenUART1(UART_EN, UART_RX_ENABLE | UART_TX_ENABLE, pbClk / 16 / DESIRED_BAUDRATE - 1);
    ConfigIntUART1(UART_INT_PR2 | UART_RX_INT_EN);
    INTEnableSystemMultiVectoredInt();
    while (BusyUART1()); // Attendo che il modulo UART sia libero

}

void main(void) {

    while (1) {

        //while (BusyUART1()); // Attendo che la UART sia libera
        /*####serve veramente?#####*/

        putcUART1('a'); // Transmit ?data? through UART
        //putcUART1('13'); // Transmit ?13? (carriage return)

        delay(1000);

        putcUART1('z'); // Transmit ?data? through UART
        //putcUART1('13'); // Transmit ?13? (carriage return)

    }

    return;
}


void __ISR(_UART1_VECTOR, ipl2) IntUart1Handler(void) {
    // Is this an RX interrupt?
    if (mU1RXGetIntFlag()) {
       
        // Clear the RX interrupt Flag
        mU1RXClearIntFlag();
        // Echo what we just received.
        putcUART1(ReadUART1());
    }
    // We don't care about TX interrupt
    if (mU1TXGetIntFlag()) {
        mU1TXClearIntFlag();
    }
}