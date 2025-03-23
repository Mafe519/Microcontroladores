//#include "C:\Micro\processing\Rotina servos teste.h"
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

#define use_servo_1
#define use_servo_2
#define use_servo_3

#define servo_1 PIN_B0
#define servo_2 PIN_B1
#define servo_3 PIN_B2

#include <servo_st.c>
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
   
   servo_init();
   servo_1_write(0);
   servo_2_write(0);
   servo_3_write(0);
   delay_ms(1000);
   
   while(true)
   {
      servo_1_write(90);
      delay_ms(1000);
      servo_2_write(90);
      delay_ms(1000);
      servo_3_write(90);
      delay_ms(1000);
      
      servo_1_write(180);
      delay_ms(1000);
      servo_2_write(180);
      delay_ms(1000);
      servo_3_write(180);
      delay_ms(1000);
      
      servo_1_write(0);
      delay_ms(1000);
      servo_2_write(90);
      delay_ms(1000);
      servo_3_write(90);
      delay_ms(1000);
      
      servo_1_write(0);
      delay_ms(1000);
      servo_2_write(0);
      delay_ms(1000);
      servo_3_write(0);
      delay_ms(1000);
      
      servo_1_write(90);
      //delay_ms(1000);
      servo_2_write(90);
      //delay_ms(1000);
      servo_3_write(90);
      //delays_ms(1000);
   }
}
