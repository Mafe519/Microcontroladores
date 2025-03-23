//#include "C:\Micro\COMLeds\mainLeds.h"
#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=6000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#define led1 PIN_D0
#define led2 PIN_D1
#define led3 PIN_D2
#define led4 PIN_D7
#define led5 PIN_D6

void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   // TODO: USER CODE!!
   int dado = 0;
   
   while(true){
      if(kbhit() > 0){
         dado = getchar();
        
      switch (dado) {
         case 'L':
            putc(dado); 
            output_high(led1);
            break;  // Mover servo 1 para a esquerda
         case 'R': 
            putc(dado); 
            output_low(led1); 
            break;  // Mover servo 1 para a direita
         case 'U':
            output_high(led2); 
            break;  // Mover servo 2 para a esquerda
         case 'D':
            output_low(led2); 
            break;  // Mover servo 2 para a direita
         case 'I':   
            output_high(led3); 
            break;  // Mover servo 3 para a esquerda
        // case 'O': 
          //  servo_3_write(180); 
            //break;  // Mover servo 3 para a direita
         
      }
      }
   }

}
