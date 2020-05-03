//LCD interfacing code adapted from lab 4 8051 lcd interfacing. 
//Authors Sharan Arumugam and Atharv Desai
#include <stdbool.h>
#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
static void delay_us(int delay);
void delay_ms(int delay_t);

void lcdBusyWait();
void lcdclear();
void check_busy_flag();
void putcommand(unsigned char x);
void commandWrite(unsigned char cmd);
void putdata(unsigned char x);
void dataWrite(unsigned char Data);
void lcdputch(char ch);
void lcdgotoaddr(unsigned char addr);
void lcdputstr(char *str, unsigned char addr);
void lcdinit();
