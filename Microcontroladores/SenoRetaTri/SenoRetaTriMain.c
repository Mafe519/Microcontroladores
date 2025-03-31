#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=20000000)

unsigned int i;

int8 seno[40]={
   0,
   10,
   20,
   30,
   40,
   50,
   60,
   69,
   79,
   88,
   98,
   107,
   116,
   125,
   133,
   142,
   150,
   158,
   166,
   173,
   180,
   187,
   194,
   200,
   206,
   212,
   217,
   222,
   227,
   232,
   236,
   239,
   243,
   245,
   248,
   250,
   252,
   253,
   254,
   255
   };
int8 tri[40]={
   249,
   242,
   236,
   230,
   223,
   217,
   210,
   204,
   198,
   191,
   185,
   179,
   172,
   166,
   159,
   153,
   147,
   140,
   134,
   128,
   121,
   115,
   108,
   102,
   96,
   89,
   83,
   77,
   70,
   64,
   57,
   51,
   45,
   38,
   32,
   26,
   19,
   13,
   6,
   0
   };
   
void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,255,1);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_OFF);
   set_pwm1_duty(512);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   // TODO: USER CODE!!
   while(true){
      for(i = 0; i < 40; i++){
         set_pwm1_duty(seno[i]);
         delay_us(250);
      }
      
      set_pwm1_duty(255);
      
      delay_ms(10);

      for(i = 0; i < 40; i++){
         set_pwm1_duty(tri[i]);
         delay_us(250);
      }
   }
}
