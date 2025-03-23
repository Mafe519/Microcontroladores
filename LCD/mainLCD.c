//#include "C:\Micro\LCD\mainLCD.h"
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

#ifndef lcd_enable
   #define lcd_enable pin_e1
   #define lcd_rs    pin_e0
   #define lcd_d4    pin_d4
   #define lcd_d5    pin_d5
   #define lcd_d6    pin_d6
   #define lcd_d7    pin_d7
#endif

#include <mod_lcd.C>

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
   
   lcd_ini();
   delay_ms();

   // TODO: USER CODE!!
   while(true){
      lcd_escreve("\f") // apaga o display
      printf(lcd_escreve,"   ifmt 2024    \r\n");
      printf(llcd_escreve,"     LCD       ");
      delay_ms(2000);
      
      lcd_escreve("\f")
      printf(lcd_escreve,"MICROCONTROLADOR");
      printf(lcd_escreve,"    E FACIL     ");
      delay_ms(2000);
      
   }

}
