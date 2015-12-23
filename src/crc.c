#include "crc.h"

unsigned int CRC16(unsigned int crc, unsigned int data)
{ 
	unsigned int LSB, i; 
	const unsigned int Poly16=0xA001; 

	crc = ((crc^data) | 0xFF00) & (crc | 0x00FF); 
	for (i=0; i<8; i++) { 
		LSB=(crc & 0x0001); 
		crc=crc/2; 
		if (LSB)  
		  crc=crc^Poly16; 
	} 
	return(crc); 
}

int checkCRC(unsigned char *buf, unsigned int len)
{
	unsigned int i;
	unsigned int Crc; 
	Crc=0xFFFF; 
	for (i=0; i<len-2; i++)
	{
		Crc = CRC16(Crc, buf[i]);
	}
	if (buf[len-2] != (Crc & 0x00FF))
		return 1;
	if (buf[len-1] != ((Crc & 0xFF00) / 256 ))
		return 1;
	return 0;
}

void appendCRC(unsigned char *buf, unsigned int len)
{
	unsigned int Crc, i; 
	Crc=0xFFFF; 
	for (i=0; i<len-2; i++)
	{
		Crc = CRC16(Crc, buf[i]);
	}
	buf[len-2] = (Crc & 0x00FF);
	buf[len-1] = (Crc & 0xFF00) / 256;
}