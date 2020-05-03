// Main routine for Audio player module with Bluetooth interface and control over playback
//Sharan arumugam and Atahrv Desai - Authors

/* DriverLib Includes */
//
#include "mp3board.h"
/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "hd44780.h"



int getchar(void);
int putchar(int _x);






int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    P2->DIR |= BIT2;
    P5->DIR |= BIT1;//commandpin
    P6->DIR |= BIT1;//clkpin
    P5->DIR |= BIT6;//rstpin
    P2->DIR &=~BIT6;//INPUT BUSY PIN
    uartinit_0();//for pc uart
    uart2_init();//for bt uart
    resetModule();
    lcdinit();

    uint8_t songnumber;
    uint8_t volume;


    P2->DIR |= BIT2;

    
    
    char menuselect; //contains received uart value and function flow is governed by received value
    while(1)
    {

        

        menuselect=getcharBT();
        //printf("Received %c\n",k);
        if(menuselect=='1') //plays first song
        {
            lcdputstr("Playing song",0);
            printf("Playing song\n\r");
            resetModule();
            sendCommand(0);
            sendCommand(0xFFFE);

        }
        else if(menuselect=='2') //stop playback
        {
            sendCommand(stop_play);
            printf("Stopping playback\n");
            lcdclear();
            lcdputstr("Stopping playback",0);
        }
        else if(menuselect=='3')//playnextsong
        {
            sendCommand(stop_play);
            if(songnumber<=maxsong)
                songnumber++;
            resetModule();
            sendCommand(songnumber);
            sendCommand(play_pause);
            printf("Playing next song\n\r");
            lcdclear();
            lcdputstr("Playing next song",0);


        }
        else if(menuselect=='4')//
        {
            sendCommand(play_pause);
            printf("Play/Pause \n\r");
            lcdclear();
            lcdputstr("Play/Pause",0);
        }
        else if(menuselect=='5') //HARD RESET
        {
            resetModule();
            songnumber=0;
            lcdclear();
            lcdputstr("Hard Reset",0);
        }
        else if(menuselect=='6') //volume change up
        {
            volume++;
            if(zerovol|volume > 0xFFF7)
            {
                volume--;
                printf("Max Volume reached\n\r");
                lcdclear();
                lcdputstr("Volume increased ",0);
            }
            else
                sendCommand(zerovol|volume);
        }
        else if(menuselect=='7')//volume change down
        {
            volume--;
            if(zerovol|volume <0xFFF0)

            {
                volume++;
                printf("Min Volume reached\n\r");
                lcdputstr("Play/Pause",0);
            }
            else
                sendCommand(zerovol|volume);
        }


        if(P2->IN &BIT6)
            printf("Songs playing\n\r");

    }

}

int getchar(void)
{
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG));
    return EUSCI_A0->RXBUF;
}

int putchar(int _x)
{
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
    EUSCI_A0->TXBUF = _x;
    return 0;
}
