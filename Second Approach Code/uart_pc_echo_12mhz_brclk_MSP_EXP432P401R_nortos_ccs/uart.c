#include "uart.h"
//contains uart initalisation functions and polling driven transmit and receive functions
//Authors Sharan Arumugam and Atharv Desai
//BAUD RATE FOR BOTH SET AT 9600
//values taken from TIS online calculator http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
//not used sets up uart communication to pc port
const eUSCI_UART_ConfigV1 uartConfig0 =
{
 EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
 19,                                     // BRDIV = 19
 8,                                       // UCxBRF = 8
 0,                                       // UCxBRS = 0
 EUSCI_A_UART_NO_PARITY,                  // No Parity
 EUSCI_A_UART_LSB_FIRST,                  // LSB First
 EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
 EUSCI_A_UART_MODE,                       // UART mode
 EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
 EUSCI_A_UART_8_BIT_LEN                  // 8 bit data length
};

const eUSCI_UART_ConfigV1 uartConfig2 = 
{
 EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
 19,                                     // BRDIV = 78
 8,                                       // UCxBRF = 2
 0,                                       // UCxBRS = 0
 EUSCI_A_UART_NO_PARITY,                  // No Parity
 EUSCI_A_UART_LSB_FIRST,                  // LSB First
 EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
 EUSCI_A_UART_MODE,                       // UART mode
 EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
 EUSCI_A_UART_8_BIT_LEN                  // 8 bit data length
};
void uartinit_0(void)
{

    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                                                   GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    
    //![Simple UART Example]
    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig0);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);


}

void uart2_init(void)
{

    
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
                                                   GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    

    //![Simple UART Example]
    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig2);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A2_BASE);

    
}

int getcharBT(void)
{
    while(!(EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG));
    return EUSCI_A2->RXBUF;
}