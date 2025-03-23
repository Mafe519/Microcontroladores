//#include "C:\Micro\timer01\mainTimer01.h"
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

#use delay(clock=20000000)

#int_RTCC
void  RTCC_isr(void) 
{  
   int8 contador;
   if(++contador>=76){
      output_toggle(PIN_D0);
      contador = 0;
   }
}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);

   // TODO: USER CODE!!
   while(true){
      output_high(PIN_D2);
      delay_ms(2000);
      output_low(PIN_D2);
      delay_ms(2000);
   }

}
