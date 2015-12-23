#ifndef _CRC_H_
#define _CRC_H_

/* Checks if array buf with size len has correct CRC or not.
	0 if it is correct, 1 if it is incorrect. */
int checkCRC(unsigned char *buf, unsigned int len);
/* Calculates CRC16 for one step. 
	This function has to be executed for every byte in modbus array.
	crc is temporary value, data is data for one step.
	Please look at checkCRC if you need example how to use it. */
unsigned int CRC16(unsigned int crc, unsigned int data);
/* Gets buf array with size len (size with CRC bytes), and append
	CRC on last 2 bytes of that array. */
void appendCRC(unsigned char *buf, unsigned int len);
#endif