//contains uart initalisation functions and polling driven transmit and receive functions
//Authors Sharan Arumugam and Atharv Desai
#include <stdbool.h>
#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


void uart2_init(void);
void uartinit_0(void);
int getcharBT(void);//receive uart signal