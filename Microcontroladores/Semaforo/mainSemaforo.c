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

 
void semaforo() {
   output_low(PIN_D0);
   output_low(PIN_D7);
   
   delay_ms(10000);
   
   output_high(PIN_D0);
   output_low(PIN_D1);
   delay_ms(3000);
   
   output_high(PIN_D1);
   output_low(PIN_D2);
   delay_ms(1000);
   output_high(PIN_D7);
   output_low(PIN_D6);
   
   delay_ms(10000);
   output_high(PIN_D6);
   int i;
   for(i=0;i<5;i++) {
      output_high(PIN_D7);
      delay_ms(500);
      output_low(PIN_D7);
      delay_ms(500);
   }
   
   delay_ms(500);
   output_high(PIN_D2);
   output_low(PIN_D0);
}

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
      output_low(PIN_D0);
      output_low(PIN_D7);
      while(input(PIN_B0));
      semaforo();
   }
}
