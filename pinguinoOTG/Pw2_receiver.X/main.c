/*
 * File:   main.c
 * Author: Usr
 *
 * Created on 13 giugno 2019, 16.39
 */

/*RECEIVER*/
/*
tested 13/6/2019 --> working
*/

#pragma config FPLLIDIV = DIV_2  // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20  // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2  // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF      // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1  // System PLL Output Clock Divider (PLL Divide by 256)
#pragma config FNOSC = PRIPLL    // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON      // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON         // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS      // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON     // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8    // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD    // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF      // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config DEBUG = OFF       // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF         // Program Flash Write Protect (Disable)
#pragma config BWP = OFF         // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF          // Code Protect (Protection Disabled)

#include <p32xxxx.h>
#include <plib.h>
#define SYSCLK 8000000
#define DESIRED_BAUDRATE 9600

int flag;
char data;

void initializeUART()
{
    OpenUART1(UART_EN, UART_RX_ENABLE | UART_TX_ENABLE, DESIRED_BAUDRATE);
    ConfigIntUART1(UART_INT_PR2 | UART_RX_INT_EN);
    INTEnableSystemMultiVectoredInt();
}

void main(void)
{

    initializeUART();
    TRISD = 0x04;   //set the pin 2 in input            //why?!
    TRISD = 0x0000; //define if input or output             //output = 0, input = 1

    while (1){

        if (flag){

            if (data == 'a'){

                TRISD = 0x0020; //light led1
            }
            if (data == 'z'){
                
                TRISD = 0x0040; //light led2
            }
            
            flag = 0;
        }
    }

    return;
}

void __ISR(_UART1_VECTOR, ipl2) IntUart1Handler(void)
{
    //RX interrupt
    if (mU1RXGetIntFlag())
    {

        data = (char)ReadUART1(); // Read data from Rx
        flag = 1;
        
        mU1RXClearIntFlag(); // Clear the RX interrupt Flag
        /
        //putcUART1(ReadUART1()); // Echo what we just received
    }
    // We don't care about TX interrupt
    if (mU1TXGetIntFlag())
    {
        mU1TXClearIntFlag();
    }
}