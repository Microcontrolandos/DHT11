/*
	DHT11.c - Humidity e Temperature Sensor library for MikroC PRO PIC
	Author: Tiago Melo
	Blog: microcontrolandos.blogspot.com.br
*/

#include "DHT11.h"

// Realiza a leitura de 1 byte
static char DHT11_Get_Byte()
{
char i, byte = 0;
unsigned timeOut;

    for( i = 0b10000000; i; i = i >> 1 )
    {
        timeOut = 0xFFFF;
		while( !DHT11_Data )
            if( !--timeOut ) return 0;

        Delay_us( 40 );

        if( DHT11_Data )
        {
            byte |= i;
            timeOut = 0xFFFF;
            while( !DHT11_Data )
                if( !--timeOut ) return 0;
        }
    }

    return byte;
}

/*
	Realiza a leitura da umidade e da temperatura do sensor DHT11
	
	Parametros:
		umidade: recebe o valor da umidade relativa
		temperatura: recebe o valor da temperatura
	
	Retorno:
		0 - a leitura ocorreu com sucesso
		1 - houve um erro de leitura causada pela demora na recepção dos dados
		2 - houve um erro de leitura causada pelo erro no checksum
*/
char DHT11_Read( char *umidade, char *temperatura )
{
char checksum = 0;
unsigned timeOut = 0xFFFF;

    DHT11_Data_Direction = 0;
    DHT11_Data = 0;
    Delay_ms( 20 );

    DHT11_Data = 1;
    DHT11_Data_Direction = 1;
    Delay_us( 60 );

    //max 80us
    while( !DHT11_Data )
        if( !--timeOut ) return DHT11_ERROR_TIMEOUT;
    timeOut = 0xFFFF;
    //max 80us
    while( DHT11_Data )
        if( !--timeOut ) return DHT11_ERROR_TIMEOUT;

    umidade[0] = DHT11_Get_Byte();
    umidade[1] = DHT11_Get_Byte();
    temperatura[0] = DHT11_Get_Byte();
    temperatura[1] = DHT11_Get_Byte();
    checksum = DHT11_Get_Byte();

    if( (char)( umidade[0] + umidade[1] + temperatura[0] + temperatura[1] ) != checksum )
        return DHT11_ERROR_CHECKSUM;

    return DHT11_OK;
}