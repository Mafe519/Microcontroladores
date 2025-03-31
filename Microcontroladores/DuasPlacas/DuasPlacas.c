// 1. Conectar duas placas PICGenios via serial. 
// 2. A placa 1 enviasse valores de 0 a 1000 para placa 2.

// 3. A placa 2 recebe o valor apresenta no LCD, divide por dois l, 
   // apresenta o resultado na segunda linha do LCD e depois envia essa metade de volta para placa 1

// 4. A placa 1 apresenta os valores enviados (linha 1) e recebidos(linha 2)

#include <16F877A.h>

#device adc=10       // configuração do AD

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD        //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=20000000)

#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#ifndef lcd_enable
   #define lcd_enable     pin_E1    // pino enable do LCD
   #define lcd_rs         pin_E2    // pino rs do LCD
   //#define lcd_rw         pin_A4    // pino rw do LCD
   #define lcd_d4         pin_d4    // pino de dados d4 do LCD
   #define lcd_d5         pin_d5    // pino de dados d5 do LCD
   #define lcd_d6         pin_d6    // pino de dados d6 do LCD
   #define lcd_d7         pin_d7    // pino de dados d7 do LCD
#endif

#include "mod_lcd.c"

