/*
 * File:   main.c
 * Author: Sander
 *
 * Created on 07 giugno 2019, 15.31
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

void init(){
 
    OpenUART1(UART_EN, UART_RX_ENABLE | UART_TX_ENABLE, BAUD_VALUE);
    // Configure UART1 RX Interrupt
    ConfigIntUART1(UART_INT_PR2 | UART_RX_INT_EN);
    // Must enable glocal interrupts - in this case, we are using multi-vector mode
    INTEnableSystemMultiVectoredInt();
    pbClk = SYSTEMConfig(SYSCLK, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
}

void main(void)
{

    init();
    while (1)
    {
            // UART 1 interrupt handler
            // it is set at priority level 2
            void __ISR(_UART1_VECTOR, ipl2) IntUart1Handler(void)
        {
            // Is this an RX interrupt?
            if (mU1RXGetIntFlag())
            {
                // Clear the RX interrupt Flag
                mU1RXClearIntFlag();
                // Echo what we just received.
                putcUART1(ReadUART1());
            }
            // We don't care about TX interrupt
            if (mU1TXGetIntFlag())
            {
                mU1TXClearIntFlag();
            }
        }
    }
    return;
}
