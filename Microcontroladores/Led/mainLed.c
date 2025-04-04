
#include <16F877A.h>
#device adc=8

#FUSES NOWDT, HS, NOPUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT, RESERVED

#use delay(clock=6000000)

void main() {

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
   
   output_high(PIN_D7);
   output_high(PIN_D6);
   output_high(PIN_D5);
   output_high(PIN_D4);
   output_high(PIN_D3);
   output_high(PIN_D2);
   output_high(PIN_D1);
   output_high(PIN_D0);
   delay_ms(100);
   
   while (true) {
   /*
      int i;
      for (i=1;i<=3;i++) {
         output_low(PIN_D0);
         delay_ms(250);
         output_high(PIN_D0);
         output_low(PIN_D1);
         delay_ms(250);
         output_high(PIN_D1);
         output_low(PIN_D2);
         delay_ms(250);
         output_high(PIN_D2);
      }
      
      delay_ms(250);
      
      for (i=1;i<=3;i++) {
         output_low(PIN_D2);
         delay_ms(250);
         output_high(PIN_D2);
         output_low(PIN_D3);
         delay_ms(250);
         output_high(PIN_D3);
         output_low(PIN_D4);
         delay_ms(250);
         output_high(PIN_D4);
      }
      
      delay_ms(250);
      
      for (i=1;i<=3;i++) {
         output_low(PIN_D4);
         delay_ms(250);
         output_high(PIN_D4);
         output_low(PIN_D5);
         delay_ms(250);
         output_high(PIN_D5);
         output_low(PIN_D6);
         delay_ms(250);
         output_high(PIN_D6);
      }
      
      delay_ms(250);
         
      output_low(PIN_D7);
      delay_ms(500);
      output_high(PIN_D7);
      delay_ms(250);
      output_low(PIN_D6);
      delay_ms(250);
      output_high(PIN_D6);
      output_low(PIN_D5);
      delay_ms(250);
      output_high(PIN_D5);
      output_low(PIN_D4);
      delay_ms(250);
      output_high(PIN_D4);
      output_low(PIN_D3);
      delay_ms(250);
      output_high(PIN_D3);
      output_low(PIN_D2);
      delay_ms(250);
      output_high(PIN_D2);
      output_low(PIN_D1);
      delay_ms(250);
      output_high(PIN_D1);
   */
   OUTPUT_D(0xf0);
   delay_ms(1000);
   OUTPUT_D(0x0f);
   delay_ms(1000);
   }
}
