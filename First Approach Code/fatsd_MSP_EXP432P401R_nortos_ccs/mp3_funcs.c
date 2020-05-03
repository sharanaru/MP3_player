#include "mp3_funcs.h"
////Code to handle VS1053 Command send and read functions and Data write instructions - Authors: Sharan Arumugam and Atharv Desai

bool read_dreq() //checks if next transaction can occue
{
    P6->DIR &=~BIT7;
    if(P6->IN & BIT7)
        return true;
    else
        return false;

}
void WriteSci( uint8_t address,uint16_t data)
{
    
    while(!(read_dreq()));
   
    clearxcs; //clearing xcs 
    spi_transmit(CMDWRITE);

    spi_transmit(address);

    uint8_t byte =0;
    byte= (data)>>8;
    spi_transmit(byte);
    byte=data&0x00FF;


    spi_transmit(byte);

    int i=0;
    while(i!=100) //time to finish last transmission
        i++;
    setxcs; //setting xcs after transmission
    while(!(read_dreq())); //checking if dreq has been st to indicate operation is open


}

uint16_t ReadSci(uint8_t address)
{   while((P6->IN & BIT7)==0);
    uint16_t readvalue=0;
    clearxcs;
    spi_transmit(CMDREAD);
    spi_transmit(address);
    EUSCI_B2->TXBUF=0XFF;
    while(!(EUSCI_B2->IFG & EUSCI_B_IFG_TXIFG)){};
    EUSCI_B2->TXBUF=0XFF;
    while(!(EUSCI_B2->IFG & EUSCI_B_IFG_TXIFG)){};
    EUSCI_B2->IFG &=~ EUSCI_B_IFG_TXIFG;

    readvalue|=(uint16_t)spi_receive()<<8;
    
    
    readvalue|=spi_receive();
    printf("received val:%d\n",readvalue);
    int i=0;
    while(i!=50) //time to finish last transmission
            i++;
    setxcs;
    return readvalue;
}


void  WriteSdi(uint8_t *data, uint8_t bytes)
{ while((P6->IN & BIT7)==0);
    if(bytes<32)
    {
        //setxdcs;
        clearxdcs;
        int i;
        for(i=0;i<bytes;i++)
        {
            spi_transmit(*data);
            data++;
        }

        int f =0;
        while(f!=50) //time to finish last transmission
            f++;
        setxdcs;
    }
    else
    {
        int bytecount=0;
        setxdcs;
        int f =0;
                while(f!=50) //time to finish last transmission
                    f++;
        clearxdcs;
        int x;
        for(x=0;x<bytes;x++,bytecount++)
        {
            if(bytecount==31)
            {
                setxdcs;
                clearxdcs;
                bytecount=0;
            }
            spi_transmit(*data);
            printf("transmitted data was %X\n",*data);
            data++;
        }
        int i=0;
        while(i!=500) //time to finish last transmission
            i++;
        setxdcs;

    }
    while(!(read_dreq()));//checking if dreq has been st to indicate operation is open
}

