//#include "C:\Micro\Miniteste\mainMiniTeste.h"
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

#define VELOCIDADE_PIN PIN_A0
#define CINTO_MOTORISTA PIN_B0
#define CINTO_PASSAGEIRO PIN_B1
#define BUZZER_PIN PIN_B2


void init_adc(){
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_2);
   set_adc_channel(0);
   delay_us(10);
}

int read_velocity(){
   int adc_value = read_adc();
   float velocity = (adc_value/255.0) * 300.0;
   return (int) velocity;
}

int is_seatBelt_on(int pin){
   return input(pin);
}

void sound_buzzer(){
   output_high(BUZZER_PIN);
   delay_us(500);
   output_low(BUZZER_PIN);
   delay_us(500);
}
void main()
{
   int velocity;
   init_adc();

   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   // TODO: USER CODE!!
   while(true){
      velocity = read_velocity();
      if(velocity > 30 && (is_seatBelt_on(CINTO_MOTORISTA) != 0 || is_seatBelt_on(CINTO_PASSAGEIRO) != 0)){
         sound_buzzer();
      } else{
         output_low(BUZZER_PIN);
      }
      
      delay_ms(10);
   }

}
