#include "mp3board.h"
//ADAPTED FROM SPARFUNS ADRUINO FIRMWARE EXAMPLE:https://github.com/sparkfun/Audio-Sound_Breakout-WTV020SD/blob/V_1.0/firmware/Audio-Sound_Breakout/AudioModule.ino
//Code written for msp432 by Sharan Arumugam and Atharv Desai
//DELAY FUNCTION USING TIMER A0
void delay(uint16_t time_needed)
{

    time=false;
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] = 2*time_needed;
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP; // SMCLK, UP mode

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;
    __enable_irq();
    NVIC->ISER[0] |= 1 << ((TA0_0_IRQn) & 31);
    while(time==false)
        ;
}

void resetModule()
{
    
    clearrstpin;
	//500 ms delay function
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(10000);
    setrstpin;
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(10000);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(10000);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(10000);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(10000);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(15700);
    delay(6800);
}
void sendCommand(unsigned int command)
{
    
    clearclkpin;
    delay(2950);//corressponds to 1900 us delay
    uint8_t i;
    for (i = 0; i < 16; i++)
    {
        delay(110);// corresponds to 100 Microseconds delay
        clearclkpin;
        clearcommandpin;
        if ((command & 0x8000) != 0)
        {
            setcommandpin;
        }
        delay(110);// corresponds to 100 Microseconds delay
        setclkpin;
        command = command<<1;
    }
}


void TA0_0_IRQHandler(void) {
    // Clear the compare interrupt flag
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    time=true;                        //setting flag
    TIMER_A0->CTL =TIMER_A_CTL_MC__STOP; //stopping timer
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE; //disabling interrupt
}

