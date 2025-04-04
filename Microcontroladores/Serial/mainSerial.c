#include <16F877A.h>
#device adc=8

#FUSES NOWDT            //No Watch Dog Timer
#FUSES HS               //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT            //No Power Up Timer
#FUSES NOPROTECT        //Code not protected from reading
#FUSES NODEBUG          //No Debug mode for ICD
#FUSES BROWNOUT         //Reset when brownout detected
#FUSES NOLVP            //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD            //No EE protection
#FUSES NOWRT            //Program memory not write protected
#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

void main()
{
   unsigned int valor =8;
   
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_16);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   while(true){
      putc('A');
      putc(65);
      putc(' ');
      putc('\n');
      delay_ms(100);
   }
}
