////Code to handle VS1053 Command send and read functions and Data write instructions - Authors: Sharan Arumugam and Atharv Desai

#include "spi_portb.h"
//xcs pin5.1 xcs

#define setxcs P5->DIR |= BIT1;P5->OUT |= BIT1; //acts as command select pin 
#define clearxcs P5->DIR |= BIT1;P5->OUT &= ~BIT1;
#define setxdcs P6->DIR |= BIT1;P6->OUT |= BIT1; //acts as data select pin
#define clearxdcs P6->DIR |= BIT1;P6->OUT &= ~BIT1;
#define CMDWRITE 0x2
#define CMDREAD 0x3
//dreq at p6.7
bool read_dreq(); //checks dreq pin to see if next operation can occur
void WriteSci( uint8_t address,uint16_t data); //command to write command code to chip
uint16_t ReadSci(uint8_t address); //reads value from cmd register
void WriteSdi(uint8_t *data, uint8_t bytes);//writes /sends data to chip buffer

