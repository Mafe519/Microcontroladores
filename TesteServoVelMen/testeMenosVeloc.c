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

#define use_servo_1
#define use_servo_2
#define use_servo_3

#define servo_1 PIN_B0
#define servo_2 PIN_B1
#define servo_3 PIN_B2

#include <servo_st.c>

// Função para movimentar o servo gradualmente
void move_servo_gradual(int servo, int from_angle, int to_angle, int step_delay) {
   int i;
   if (from_angle < to_angle) {
      for (i = from_angle; i <= to_angle; i++) {
         if (servo == 1) {
            servo_1_write(i);
         } else if (servo == 2) {
            servo_2_write(i);
         } else if (servo == 3) {
            servo_3_write(i);
         }
         delay_ms(step_delay);
      }
   } else {
      for (i = from_angle; i >= to_angle; i--) {
         if (servo == 1) {
            servo_1_write(i);
         } else if (servo == 2) {
            servo_2_write(i);
         } else if (servo == 3) {
            servo_3_write(i);
         }
         delay_ms(step_delay);
      }
   }
}

void main() {
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   servo_init();
   servo_1_write(0);
   servo_2_write(0);
   servo_3_write(0);
   delay_ms(1000);

   while(true) {
      move_servo_gradual(1, 0, 90, 20); // Move servo 1 de 0 a 90 graus
      delay_ms(1000);
      move_servo_gradual(2, 0, 90, 20); // Move servo 2 de 0 a 90 graus
      delay_ms(1000);
      move_servo_gradual(3, 0, 90, 20); // Move servo 3 de 0 a 90 graus
      delay_ms(1000);

      move_servo_gradual(1, 90, 180, 20); // Move servo 1 de 90 a 180 graus
      delay_ms(1000);
      move_servo_gradual(2, 90, 180, 20); // Move servo 2 de 90 a 180 graus
      delay_ms(1000);
      move_servo_gradual(3, 90, 180, 20); // Move servo 3 de 90 a 180 graus
      delay_ms(1000);

      move_servo_gradual(1, 180, 0, 20); // Move servo 1 de 180 a 0 graus
      delay_ms(1000);
      move_servo_gradual(2, 180, 90, 20); // Move servo 2 de 180 a 90 graus
      delay_ms(1000);
      move_servo_gradual(3, 180, 90, 20); // Move servo 3 de 180 a 90 graus
      delay_ms(1000);

      move_servo_gradual(1, 0, 90, 20); // Move servo 1 de 0 a 90 graus
      delay_ms(1000);
      move_servo_gradual(2, 0, 0, 20); // Move servo 2 de 0 a 0 graus
      delay_ms(1000);
      move_servo_gradual(3, 0, 0, 20); // Move servo 3 de 0 a 0 graus
      delay_ms(1000);
   }
}

