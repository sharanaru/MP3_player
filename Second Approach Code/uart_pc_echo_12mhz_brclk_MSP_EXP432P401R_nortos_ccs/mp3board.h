//ADAPTED FROM SPARFUNS ADRUINO FIRMWARE EXAMPLE:https://github.com/sparkfun/Audio-Sound_Breakout-WTV020SD/blob/V_1.0/firmware/Audio-Sound_Breakout/AudioModule.ino
//Code written for msp432 by Sharan Arumugam and Atharv Desai

#include <stdbool.h>
#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define setcommandpin P5->OUT |= BIT1
#define clearcommandpin P5->OUT &= ~BIT1
#define setclkpin P6->OUT |= BIT1
#define clearclkpin P6->OUT &= ~BIT1
#define setrstpin P5->OUT |= BIT6
#define clearrstpin P5->OUT &= ~BIT6
#define play_pause 0xFFFE //command value to be sent to play/pause
#define maxsong 4 //no.of songs on sd card
#define stop_play 0xFFFF// command value to stops all playback
#define zerovol 0xFFF7 // max volume
bool time;
void delay(uint16_t time_needed);//generates delay using timer
void resetModule(); //toggles reset pin to reset the module
void sendCommand(unsigned int command);// sends command patterns through data pin of module
void TA0_0_IRQHandler(void) ; //timer isr routine
