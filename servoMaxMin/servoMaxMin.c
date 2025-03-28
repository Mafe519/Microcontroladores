//#include "C:\Micro\servoMaxMin\servoMaxMin.h"

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


void Rotation0() //0 Degree
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(500); // pulse of 800us
         output_low(PIN_D0);
         delay_us(19500);
         }
    }
void Rotation45() //44 Degree
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(1150); // pulse of 800us        // 1400  - 180o
         output_low(PIN_D0);                      //   x      45o
         delay_us(18850);
         }
    }
void Rotation75() //75o Degree
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(1383); // pulse of 800us        // 1400  - 180o
         output_low(PIN_D0);                      //   x      75o
         delay_us(18617);
         }
    }    

void Rotation90() //90 Degree
   {            
   unsigned int i;
   for(i=0;i<50;i++)
      {                         //  180o   0o
         output_high(PIN_D0);    // 2200 - 800 = 1400     90o =  700
         delay_us(1500); // pulse of 1500us
         output_low(PIN_D0);
         delay_us(18500);
      }
   }

void Rotation180() //180 Degree
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(2500); // pulse of 2200us
         output_low(PIN_D0);
         delay_us(17500);
      }
   }
   

void R0() //90�-
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(1000); // pulse of 2200us
         output_low(PIN_D0);
         delay_us(19000);
      }
   }
void R180() //90�+
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(2000); // pulse of 2200us
         output_low(PIN_D0);
         delay_us(18000);
      }
   }

void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   while(true){
     // R0();
      Rotation0();   // 0 graus
      delay_ms(4000);
      Rotation180(); // 180 graus
     // R180();
      delay_ms(4000);
   }
}
