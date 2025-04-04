//#include "C:\Micro\servoMirror\ServoMirrorMain.h"
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

void main()
{
   unsigned long anguloMedia=0;
   unsigned long adc_valor;
   //unsigned int angulo = 0;
   unsigned int i =0;
   unsigned long pulse_width;
   
   setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   // TODO: USER CODE!
   
   while(true){
     adc_valor = 0;
      for(i = 0; i < 4; i++){
         adc_valor += read_adc();
         delay_us(20);
      } 
      
      anguloMedia = adc_valor/4;
      
     
     /* angulo = (unsigned int)(anguloMedia*180)/255;  //(adc_valor*180/(3*275))
      
      Rotation(angulo);
      
      delay_ms(50);*/
      
    
     pulse_width = 9.80 * anguloMedia;
      
      output_high(PIN_D0);
      delay_us(pulse_width);
      output_low(PIN_D0);
      delay_us(20000 - pulse_width);
     
     delay_us(50);
    
   }  
  
}


