#ifndef _ANSPARSER_H_
#define _ANSPARSER_H_

/* This is an offsets in ORNO reply for every value.
    MODBUS_HEADER is standard Modbus RTU reply header */
#define MODBUS_HEADER 3
#define OFFSET_VOL MODBUS_HEADER
#define OFFSET_AMP MODBUS_HEADER+2
#define OFFSET_FREQ MODBUS_HEADER+4
#define OFFSET_ACTPOW MODBUS_HEADER+6
#define OFFSET_REACTPOW MODBUS_HEADER+8
#define OFFSET_APPPOW MODBUS_HEADER+10
#define OFFSET_POWFACT MODBUS_HEADER+12
#define OFFSET_ACTENERGY MODBUS_HEADER+14
#define OFFSET_REACTENERGY MODBUS_HEADER+18
#define OFFSET_ADDRESS MODBUS_HEADER+30
#define OFFSET_BDRATE MODBUS_HEADER+28

typedef struct _OrnoReply
{
    float Volts;
    float Amperage;
    float Frequency;
    unsigned int ActivePower;
    unsigned int ReactivePower;
    unsigned int ApparentPower;
    unsigned int PowerFactor;
    unsigned int ActiveEnergy;
    unsigned int ReactiveEnergy;
    unsigned int MeterAddress;
    unsigned int MeterBDRate;
} OrnoReply;

/* Parses ORNO reply array into OrnoReply structure */
OrnoReply parseAnswer(unsigned char *buf);
/* Prints OrnoReply structure in human-readable format */
void printAnswer(OrnoReply reply);
#endif