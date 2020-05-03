//Sharan Arumugam -MSP432 audio player
//Code derived from C code example given by manufacture in VS1053 APPLICATION NOTE: PLAYBACK AND RECORDING. CODE ONLY REQUIRED FOR MICROCNTROLLER PSPECIFIC SPI FUNCTIONS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define setxreset P6->DIR |= BIT6;P5->OUT |= BIT6;
#define clearxreset P6->DIR |= BIT6;P5->OUT &= ~BIT6;
#include "mp3_funcs.h"
#include "vs10xx_uc.h"

u_int32 ReadVS10xxMem32Counter(u_int16 addr);
u_int32 ReadVS10xxMem32(u_int16 addr) ;
u_int16 ReadVS10xxMem(u_int16 addr) ;
void WriteVS10xxMem(u_int16 addr, u_int16 data);
void WriteVS10xxMem32(u_int16 addr, u_int32 data);
static u_int16 LinToDB(unsigned short n);
void LoadPlugin(const u_int16 *d, u_int16 len);
void VS1053PlayFile(FILE *readFp);
void Set16(u_int8 *d, u_int16 n);
int VSTestInitHardware(void) ; //init function puts chip in known state by toggling the reset pin
int VSTestInitSoftware(void); //software init function to set up with proper values and  perform command read to verify if spi fucntions work properly
//int VSTestHandleFile(const char *fileName, int record);
