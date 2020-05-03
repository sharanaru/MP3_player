//Code to handle VS1053 SPI bus - Authors: Sharan Arumugam and Atharv Desai
#include "spi_portb.h"
volatile uint8_t RXData = 0;
volatile bool bool_rx=0;

void spi_init()
{
             // Configure SPI for port 3 , other port for SD card
             EUSCI_B2->CTLW0 = 0;
             EUSCI_B2->CTLW0 |= EUSCI_B_CTLW0_SWRST; // Put eUSCI in reset
             EUSCI_B2->CTLW0 |= EUSCI_B_CTLW0_MST; //MSP432 in master mode
             EUSCI_B2->CTLW0 |= EUSCI_B_CTLW0_MSB; //MSB first mode
             EUSCI_B2->CTLW0 |= EUSCI_B_CTLW0_SYNC; //Synchronous
             EUSCI_B2->CTLW0 |= (EUSCI_B_CTLW0_CKPH); // Clock phase bit set high as per datasheet requirements
             EUSCI_B2->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK|EUSCI_B_IE_RXIE0; //Clock source selected as ACLK and receive interrupt enabled
             EUSCI_B2->BRW = 6; //This divides output frequency, by 6, 
							
             //Configure GPIO pins to act as spi bus

             P3->SEL0 |= BIT5 | BIT6 | BIT7;
             P3->SEL1 &= ~(BIT5 | BIT6 | BIT7);
             //restart the state machine
             EUSCI_B2->CTLW0 &= ~(UCSWRST);
             //restart the state machine
             
			 __enable_irq();
    // Enable eUSCI_B0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIB2_IRQn) & 31);

}
void spi_transmit(uint8_t datain)
{  //P6->OUT |= BIT4;


    EUSCI_B2->TXBUF = datain;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));




    //P6->OUT &= ~BIT4;
}
uint8_t spi_receive()
{

while(!bool_rx)
    ;

bool_rx=false;
return RXData;
}

void EUSCIB2_IRQHandler(void)
{

    if (EUSCI_B2->IFG & EUSCI_B_IFG_RXIFG)
        {
        
        bool_rx=true;
        RXData = EUSCI_B2->RXBUF;
        }

    
    EUSCI_B2->IFG &= ~EUSCI_B_IFG_RXIFG;

}
