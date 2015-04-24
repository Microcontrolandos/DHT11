/*
	DHT11.h - Humidity e Temperature Sensor library for MikroC PRO PIC
	Author: Tiago Melo
	Blog: microcontrolandos.blogspot.com.br
*/

extern sfr sbit DHT11_Data;
extern sfr sbit DHT11_Data_Direction;

#define DHT11_OK 0
#define DHT11_ERROR_TIMEOUT 1
#define DHT11_ERROR_CHECKSUM 2

/* private */
static char DHT11_Get_Byte();

/* public */
char DHT11_Read( char *umidade, char *temperatura );