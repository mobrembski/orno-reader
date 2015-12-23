#include <stdio.h>
#include "ansparser.h"

const char* translateMeterBDRate(unsigned int mode)
{
    switch(mode)
    {
        case 1:
            return "1200";
        case 2:
            return "2400";
        case 3:
            return "4800";
        case 4:
            return "9600";
        default:
            return "ERR";
    }
}

OrnoReply parseAnswer(unsigned char *buf)
{
    OrnoReply t;
    unsigned int tmp = 0;
    tmp = (buf[OFFSET_VOL]<<8) | (buf[OFFSET_VOL+1]);
    t.Volts = (float)tmp / 10;
    tmp = (buf[OFFSET_AMP]<<8) | (buf[OFFSET_AMP+1]);
    t.Amperage = (float)tmp / 10;
    tmp = (buf[OFFSET_FREQ]<<8) | (buf[OFFSET_FREQ+1]);
    t.Frequency = (float)tmp / 10;
    t.ActivePower = (buf[OFFSET_ACTPOW]<<8) | (buf[OFFSET_ACTPOW+1]);
    t.ReactivePower = (buf[OFFSET_REACTPOW]<<8) | (buf[OFFSET_REACTPOW+1]);
    t.ApparentPower = (buf[OFFSET_APPPOW]<<8) | (buf[OFFSET_APPPOW+1]);
    t.PowerFactor = (buf[OFFSET_POWFACT]<<8) | (buf[OFFSET_POWFACT+1]);
    t.ActiveEnergy = (buf[OFFSET_ACTENERGY]<<24) |
        (buf[OFFSET_ACTENERGY+1]<<16) | 
        (buf[OFFSET_ACTENERGY+2]<<8) |
        (buf[OFFSET_ACTENERGY+3]);
    t.ReactiveEnergy = (buf[OFFSET_REACTENERGY]<<24) |
        (buf[OFFSET_REACTENERGY+1]<<16) |
        (buf[OFFSET_REACTENERGY+2]<<8) |
        (buf[OFFSET_REACTENERGY+3]);
    t.MeterAddress = (buf[OFFSET_ADDRESS]<<8) | (buf[OFFSET_ADDRESS+1]);
    t.MeterBDRate = (buf[OFFSET_BDRATE]<<8) | (buf[OFFSET_BDRATE+1]);
    return t;
}

void printAnswer(OrnoReply reply)
{
    printf("Meter address: %u\n", reply.MeterAddress);
    printf("Meter baudrate: %s\n", translateMeterBDRate(reply.MeterBDRate));
    printf("Voltage: %.1f V\n", reply.Volts);
    printf("Amperage: %.1f A\n", reply.Amperage);
    printf("Frequency: %.1f Hz\n", reply.Frequency);
    printf("Active power: %u W\n", reply.ActivePower);
    printf("Reactive power: %u var\n", reply.ReactivePower);
    printf("Apparent power: %u VA\n", reply.ApparentPower);
    printf("Power factor: %d\n", reply.PowerFactor);
    printf("Active Energy: %u Wh\n", reply.ActiveEnergy);
    printf("Reactive Energy: %u varh\n", reply.ReactiveEnergy);
}