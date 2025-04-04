#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES XT                       //Crystal osc <= 4mhz for PCM/PCH , 3mhz to 10 mhz for PCD
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=4000000)

#define  DELAY 20
#define  TIMER 10

byte const unidade[10]={
   0b11111110,    //0
   0b00111000,    //1
   0b11011101,    //2
   0b01111101,    //3
   0b00111011,    //4
   0b01110111,    //5
   0b11110111,    //6
   0b00111100,    //7
   0b11111111,    //8
   0b01111111     //9
   };
byte const dezena[10]={
   0b11101110,    //0
   0b00101000,    //1
   0b11001101,    //2
   0b01101101,    //3
   0b00101011,    //4
   0b01100111,    //5
   0b11100111,    //6
   0b00101100,    //7
   0b11101111,    //8
   0b01101111     //9
   };

void main()
{
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   //Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!

   while(true) {
      int i, j, u, d;
      for(i=0; i<100; i++) {
         d = i/10;
         u = i%10;
         for(j=0; j<TIMER; j++) {
            output_b(unidade[u]);
            delay_ms(DELAY);
            output_b(dezena[d]);
            delay_ms(DELAY);
         }
      }
      for(i=98; i>0; i--) {
         d = i/10;
         u = i%10;
         for(j=0; j<TIMER; j++) {
            output_b(unidade[u]);
            delay_ms(DELAY);
            output_b(dezena[d]);
            delay_ms(DELAY);
         }
      }
   }
}
