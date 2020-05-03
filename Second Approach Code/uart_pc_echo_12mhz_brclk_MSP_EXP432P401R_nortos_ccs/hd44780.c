////Code to handle LCD interfacing - Authors: Sharan Arumugam and Atharv Desai

#include "hd44780.h"
static void delay_us(int delay){
    int i;
    for(i=0;i<delay/1000; i++){
    }
}

/*Generates a delay*/
void Delayms(int delay){
    int i;
    for(i=0;i<delay; i++){
    }
}


/*
    CHECKS BUSY FLAG
 */
void lcdBusyWait(){
    unsigned char cmd;
    P5->OUT &= ~BIT0; //RS = 0 //command
    P5->OUT |=  BIT4; //RW = 1 //read
    cmd = readlcddata();
    while((cmd & 0x80) == 0x80){ //checking if BF is set
        cmd = readlcddata();
        P5->OUT &= ~BIT5; //Enable = 0
    };
}



/* checks for lcd busy flag */
void check_busy_flag(){
    volatile unsigned char temp;
    P5->OUT &= ~BIT0; //RS = 0 //command
    P5->OUT |=  BIT4; //RW = 1 //read
    do{
        temp = readlcddata();
        temp = temp & 0x80;
        P5->OUT &= ~BIT5; //Enable = 0
    }while(temp == 0x80);
    P5->OUT &=~  BIT4; //RW = 1 //read
}




/*
    
 */
void commandWrite(unsigned char cmd){
    P5->OUT &= ~BIT0; //RS = 0
    P5->OUT &= ~BIT4; //RW = 0
    P5->OUT &= ~BIT0; //RS = 0 //command
    P5->OUT &= ~BIT4; //RW = 0 //write
    //write command to lcd
    putcommand(cmd);
}

/*
    Name: putdata()
    Description: puts data to LCD
    Input: unsigned char
    Return value: void
 */
void putdata(unsigned char x){
    //Using port 4 to put the word to LCD
    P5->OUT |= BIT5; //Enable = 1
    Delayms(20);
    P4->DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;
    P4->OUT = x;
    Delayms(200);
    P5->OUT &= ~BIT5; //Enable = 0
}


/*
    Name: datawrite()
    Description: Writes data to LCD
    Input: unsigned char Data
    Return Value: void
 */
void dataWrite(unsigned char Data){
    P5->OUT &= ~BIT0; //RS = 0 //data
    P5->OUT |= BIT4; //RW = 1 //write
    putdata(Data);
}


/*
    Name: dataRead()
    Description: Writes data to LCD
    Input: unsigned char Data
    Return Value: void
 */
char dataRead(void){
    lcdBusyWait();
    P5->OUT |= BIT0; //RS = 1 //data
    P5->OUT |= BIT4; //RW = 1 //read
    return readlcddata();
}

/*
    Name: lcdputch()
    Description: Writes the specific character to the current
                 LCD cursor position. Should call lcdbusywait()
    Input: void
    Return Value: void
 */
void lcdputch( char ch){
    lcdBusyWait();
    P5->OUT |= BIT0; //RS = 1 //data
    P5->OUT &= ~BIT4; //RW = 0 //write
    delay_ms(2);
    putdata(ch);
}

/*
    Name: lcdgotoaddr()
    Description: Sets the cursor to the LCD DDRAM address corresponding
                 to the LCD screen. Should call lcdbusywait()
    Input: unsigned char addr
    Return Value: void
 */
void lcdgotoaddr(unsigned char addr){
    //calls set DD RAM address command
    //command is 1 DDRAM address or 1 A A A A A A A
    lcdBusyWait();
    addr |= 0x80;
    commandWrite(addr);
}








/*
    Name: lcdputstr()
    Description: Clears the LCD display and prints on the screen
    Input: char *str
    Return Value: void
 */
void lcdputstr(char *str, unsigned char addr) {
    unsigned int i = 0;
    int lineNumber = 1;
    unsigned char c;
    lcdBusyWait();
    P5->OUT |= BIT0; //RS = 1 //data
    P5->OUT &= ~BIT4; //RW = 0 //write
    c = *str;
    if(addr == 0){
        while(c){
            if(i % 16 == 0){
                if(i!=0)
                    lineNumber++;
                if(i % 64 == 0){
                    lcdgotoaddr(0x00);
                    lineNumber = 1;
                }
                if(lineNumber == 1){
                    lcdgotoaddr(0x00);
                }
                else if(lineNumber == 2){
                    lcdgotoaddr(0x40);
                }
                else if(lineNumber == 3){
                    lcdgotoaddr(0x10);
                }
                else if(lineNumber == 4){
                    lcdgotoaddr(0x50);
                    lineNumber = 1;
                }
            }
            i++;
            lcdputch(c);
            c=*(str+i);
        }
    }
    else{
        lcdgotoaddr(addr);
        while(c){
            if(i % 16 == 0){
                if(i!=0)
                    lineNumber++;
                if(i % 64 == 0){
                    lineNumber = 1;
                }
                if(lineNumber == 1){
                }
                else if(lineNumber == 2){
                }
                else if(lineNumber == 3){
                }
                else if(lineNumber == 4){
                    lineNumber = 1;
                }
            }
            i++;
            lcdputch(c);
            c=*(str+i);
        }
    }
}

void lcdinit(){
    P5->DIR |= BIT0 | BIT4 | BIT5;   //Sets P5.0,5.1, 5.5 as output pins
    P4->DIR = 0xFF;
    P4->OUT = 0x00;
    P5->OUT &= ~BIT5; //Enable = 0
    P5->OUT &= ~BIT0; //RS = 0
    P5->OUT &= ~BIT4; //RW = 0
    //1. Power on
    //2. Wait for more than 15 ms after Vcc rises to 4.5 V
    Delayms(200);
    //3. RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0 - 000011****
    commandWrite(0x30);
    //4. Wait for more than 4.1 ms
    Delayms(80);
    //5. RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0 - 000011****
    commandWrite(0x30);
    //6. Wait for more than 100 micro s
    delay_us(2000);
    //7. RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0 - 000011****
    commandWrite(0x30);
    lcdBusyWait();
    //8. Function set command
    //Function set is 0 0 1 DL N F * *
    //DL - sets interface data length, DL = 0 means 4-bit interface, DL = 1 means 8-bit interface
    //N - sets number of display line, N = 0 is 1/8 duty means 1 line, N = 1 is 1/16 duty means 2 lines
    //F - sets the character font, F = 0 means 5x7 dots, F = 1 means 5x10 dots
    //0011100 is 0x38 (DL = 1, N = 1, F = 0)
    commandWrite(0x38);
    lcdBusyWait();
    //9. Display turn OFF
    //Display On Off control is 0 0 0 0 1 D C B
    //D - sets on or off the display, D = 0 means display OFF, D = 1 means display ON
    //C - cursor on or off, C = 0 means cursor OFF, C = 1 means cursor ON
    //B - blink of cursor position character, B = 0 means cursor blink OFF, B = 1 means cursor blink ON
    //00001000 (D=0, C=0, B=0) turns the display off is 0x08 in hex
    commandWrite(0x08);
    lcdBusyWait();
    //10. Display turn ON
    //Display On Off control is 0 0 0 0 1 D C B
    //D - sets on or off the display, D = 0 means display OFF, D = 1 means display ON
    //C - cursor on or off, C = 0 means cursor OFF, C = 1 means cursor ON
    //B - blink of cursor position character, B = 0 means cursor blink OFF, B = 1 means cursor blink ON
    //00001111 (D=1, C=1, B=1) turns the display on, cursor on and blinks the cursor is 0x0F in hex
    commandWrite(0x0F);
    lcdBusyWait();
    //11. Entry mode set command
    //0 0 0 0 0 0 0 1 I/D S
    //I/D sets the cursor move direction, I/D = 1 increments cursor position, I/D = 0 decrements cursor position
    //S is for shifting display, S=0 means no display shift, S=1 means display shifts
    //0000000110 is entry mode set, with cursor moving to right. It is 0x06 in hex
    commandWrite(0x06);
    lcdBusyWait();
    //12. Clear screen
    commandWrite(0x01);
    lcdBusyWait();
    //13. Cursor home
    commandWrite(0x02);

}

