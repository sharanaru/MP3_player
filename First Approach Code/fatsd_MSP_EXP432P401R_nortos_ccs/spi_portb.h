//// Authors: Sharan Arumugam and Atharv Desai
//MSP432 audio player
//SPI drivers for VS1053b breakout board. These functions are called by the player functions defined in a seperate file. 
#include "ti/devices/msp432p4xx/inc/msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void spi_init(); //sets up spi port settings. Initialises port pins and clock frequency
void spi_transmit(uint8_t datain);//responsible for transmitting data on spi bus
uint8_t spi_receive(); // responsible for receiving data on bus. returns 8 bit value 
void EUSCIB2_IRQHandler(void);
