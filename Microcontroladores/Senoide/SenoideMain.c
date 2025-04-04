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

int8 ton[50]={
   0,
   4,
   8,
   12,
   16,
   20,
   24,
   28,
   32,
   35,
   39,
   43,
   47,
   50,
   54,
   58,
   61,
   65,
   68,
   71,
   75,
   78,
   81,
   84,
   87,
   90,
   93,
   95,
   98,
   100,
   103,
   105,
   107,
   109,
   111,
   113,
   115,
   117,
   118,
   119,
   121,
   122,
   123,
   124,
   125,
   125,
   126,
   126,
   127,
   127
   };

void main()
{
   int8 i;
   
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,182,1);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_OFF);
   set_pwm1_duty(512);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   // TODO: USER CODE!!
   while(true){
      for(i=0;i<50;i++){
         set_pwm1_duty(127+ton[i]);
         delay_us(100);
      }
      
      for(i=48;i>0;i--){
         set_pwm1_duty(127+ton[i]);
         delay_us(100);
      }
      
      for(i=0;i<50;i++){
         set_pwm1_duty(127-ton[i]);
         delay_us(100);
      }
      
      for(i=48;i>0;i--){
         set_pwm1_duty(127-ton[i]);
         delay_us(100);
      }
   }
}
