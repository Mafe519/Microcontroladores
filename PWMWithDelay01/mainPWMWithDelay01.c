//#include "C:\Micro\PWMWithDelay01\mainPWMWithDelay01.h"
#include <16F628A.h>


#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=4000000)
int16 ton, toff;
unsigned int count=0;

void main()
{

   // TODO: USER CODE!!
   if(++ton >= 1000)ton=0;
   toff = 1000 - ton;
   while(true){
      for(count=1;count <= 10; count++){
         output_high(PIN_A0);
         delay_us(ton);
         output_low(PIN_A0);
         delay_us(toff);
      }
   }

}
