//#include "C:\Micro\tarefaPWM.h"


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

unsigned int8 ton[81]={
     127,  132,  137,  142,  147,  152,  157,  162,  167,
     171,  176,  181,  185,  190,  194,  198,  202,  206,
     210,  214,  218,  221,  224,  228,  231,  233,  236,
     239,  241,  243,  245,  247,  249,  250,  251,  253,  
     253,  254,  255,  255,  255,  254,  254,  253,  252,
     252,  250,  249,  248,  246,  244,  242,  240,  238,  
     235,  233,  230,  227,  224,  220,  217,  213,  209,
     206,  202,  198,  193,  189,  185,  180,  176,  171,
     166,  161,  157,  152,  147,  142,  137,  132,  127};

unsigned int8 ton2[80]={
     127, 122,  117,  112,  107,  102,  97,  93,  88,  83,  78,  74,
     69,  65,  61,  56,  52, 48,   45,  41,  37,  34,  30,  27,
     24,  21,  19,  16,  14, 12,   10,  8,   6,   5,   4,   2,
     2,   1,   0,   0,   0,   0,   1,   2,   2,   4,   5,   6,
     8,   10,  12,  14,  16,  19,  21,  24,  27,  30,  34,  37,
     41,  45,  48,  52,  56,  61,  65,  69,  74,  78,  83,  88,
     93,  97,  102, 107, 112, 117, 122,   127 };

void main()
{

   unsigned int8 i;
   unsigned int16 t;
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_4,249,1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(0);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   while(true){
      for(i=0;i<82;i++){
        set_pwm1_duty(ton[i]);
        delay_us(48);
      }
  
      for(i=0;i<81;i++){
        set_pwm1_duty(ton2[i]);
        delay_us(48);
     }
   }
}
