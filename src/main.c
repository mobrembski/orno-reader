/*
    Main program. Version 1.0.
    Michał Obrembski (byku@byku.com.pl)

    Using rs232.c library from Teunis van Beelen
    http://www.teuniz.net/RS-232/
*/
#include <stdlib.h>
#include <stdio.h>
#include "ansparser.h"
#include "crc.h"
#include "rs232.h"

const int cport_nr = 16;
const int brate = 9600;
const char mode[]={'8','N','1',0};

/* This is standard MODBUS RTU query frame. It has following meaning:
    0x01 - MODBUS slave no. 0x01...
    0x03 - ...Read Your Holding Registers...
    0x00 0x00 - ...from register 0
    0x00 0x10 - ...to register 16
    0x00 0x00 - Last bytes is CRC16, it will be calculated.*/
unsigned char req[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00};
unsigned char buf[128];
/* Calculate time needed to wait before all bytes has been received.
    In usec. It only calculates transmission time.*/
long calcSleepTime(int bdRate, unsigned int bytesToRecv)
{
    int bytesPerSec = bdRate / 8;
    float sum = (float)bytesToRecv / (float)bytesPerSec;
    return sum * 1000000;
}

int main() 
{
    unsigned int i;
    if(RS232_OpenComport(cport_nr, brate, mode))
    {
        printf("Can not open comport\n");
        exit(1);
    }
    appendCRC(req, 8);
    i = RS232_SendBuf(cport_nr, req, 8);
    /* It seems that ORNO Power meters need 0.2 sec to prepare reply*/
    usleep(calcSleepTime(9600, i) + 200000);
    i = RS232_PollComport(cport_nr,buf,37);

    if (checkCRC(buf, i))
    {
        printf("Wrong CRC!\n");
        exit(1);
    }
    OrnoReply t = parseAnswer(buf);
    printAnswer(t);

    RS232_CloseComport(cport_nr);
    return 0;
}