# DHT11
Humidity e Temperature Sensor

> O DHT11 é um sensor de temperatura e umidade que permite fazer leituras de temperaturas entre 0 a 50 Celsius e umidade entre 20 a 90%.

>
* Faixa de medição de umidade: 20 a 90% UR
* Faixa de medição de temperatura: 0° a 50°C
* Alimentação: 3V - 5V
* Corrente: 200uA a 500mA, em stand by de 100uA a 150 uA
* Precisão de umidade de medição: ± 5,0% UR
* Precisão de medição de temperatura: ± 2.0 °C
* Tempo de resposta: 2s

#### EXEMPLO

```c
#include "DHT11.h"

/* Pinos do display LCD */
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;

/* Pino do sensor DHT11 */
sbit DHT11_Data at RB6_bit;
sbit DHT11_Data_Direction at TRISB6_bit;

/* Variáveis */
char umidade[2], temperatura[2];
char texto[6]; // 000°C ou 000%

void main()
{
      // Inicializa o display LCD
      Lcd_Init();
      Lcd_Cmd( _LCD_CLEAR );
      Lcd_Cmd( _LCD_CURSOR_OFF );
      
      while( 1 )
      {
        // Realiza a leitura da umidade e temperatura
        if( DHT11_Read( &umidade, &temperatura ) == DHT11_OK )
        {
          Lcd_Out( 1, 1, "UMIDADE: " );
          ByteToStr( umidade[0], texto );
          texto[3] = '%';
          texto[4] = 0;
          Lcd_Out_CP( texto );

          Lcd_Out( 2, 1, " TEMP: " );
          ByteToStr( temperatura[0], texto );
          texto[3] = 223; //°
          texto[4] = 'C';
          texto[5] = 0;
          Lcd_Out_CP( texto );
        }
        
        Delay_ms( 2000 );
      }

}
```
