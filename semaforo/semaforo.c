//#include "C:\Micro\semaforo.h"

#include <16F877A.h>

#device ADC=8


#FUSES NOWDT               //No Watch Dog Timer

#FUSES NOBROWNOUT //No brownout reset

#FUSES NOLVP  //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#define verde PIN_D0
#define amarelo PIN_D1
#define vermelho PIN_D2
#define vermelhoP PIN_D7
#define verdeP PIN_D6

#use delay(crystal=6000000)

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
   while(true) {
      while(input(PIN_B0)){
         output_low(verde);
         output_low(vermelhoP);
      }
      delay_ms(10000);
      
      output_high(verde);
      output_low(amarelo);
      delay_ms(3000);
      
      output_high(amarelo);
      
      output_low(vermelho);
      delay_ms(1000);
      
      output_high(vermelhoP);
      output_low(verdeP);
      
      delay_ms(10000);
      output_high(verdeP);
      
      output_low(vermelhoP);
      delay_ms(625);
      output_high(vermelhoP);
      delay_ms(625);
      output_low(vermelhoP);
      delay_ms(625);
      output_high(vermelhoP);
      delay_ms(625);
      output_low(vermelhoP);
      delay_ms(625);
      output_high(vermelhoP);
      delay_ms(625);
      output_low(vermelhoP);
      delay_ms(625);
      output_high(vermelhoP);
      delay_ms(625);
      
      output_low(vermelhoP);
      delay_ms(1000);
      
     
      output_high(vermelho);
   }
}
