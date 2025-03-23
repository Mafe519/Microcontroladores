//#include "C:\Micro\ControleServos\ControleBracosMain.h"
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

#use delay(clock=8000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)


#define use_servo_1
#define use_servo_2
#define use_servo_3 

#define servo_1 PIN_B0
#define servo_2 PIN_B1
#define servo_3 PIN_B2

#include <servo_st.c>

/*void move_servo_smoothly(int servo, int target_position) {
   int current_position;
   
   // Determinar a posição atual do servo
   switch (servo) {
      case 1: current_position = servo_1_read(); break;
      case 2: current_position = servo_2_read(); break;
      case 3: current_position = servo_3_read(); break;
   }
   
   // Mover o servo em pequenos passos até a posição alvo
   while (current_position != target_position) {
      if (current_position < target_position) {
         current_position++;
      } else {
         current_position--;
      }
      
      switch (servo) {
         case 1: servo_1_write(current_position); break;
         case 2: servo_2_write(current_position); break;
         case 3: servo_3_write(current_position); break;
      }
      
      delay_ms(20); // Pequeno delay para suavizar o movimento
   }
} */

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

   // TODO: USER CODE!!
 
   
   //servo_init();
   servo_1_write(0);  // Posição inicial
   servo_2_write(0);  // Posição inicial
   servo_3_write(0);  // Posição inicial

   while(true) {
     // check_bluetooth_command();
     
      int dado = 0;
        
      if(kbhit()> 0){
         dado = getchar();
         
        char dado1 = (char) dado;
        
      switch (dado) {
         case 'L':
           // putc(dado); 
            servo_1_write(90);
            break;  // Mover servo 1 para a esquerda
         case 'R': 
           // putc(dado); 
            servo_1_write(180);
            break;  // Mover servo 1 para a direita
         case 'U':
          //  putc(dado);
            servo_2_write(90); 
            break;  // Mover servo 2 para a esquerda
         case 'D':
         //   putc(dado);
            servo_2_write(180); 
            break;  // Mover servo 2 para a direita
         case 'I':
          //  putc(dado);
            servo_3_write(90); 
            break;  // Mover servo 3 para a esquerda
         case 'O': 
          //  putc(dado);
            servo_3_write(180); 
            break;  // Mover servo 3 para a direita
         
      }  
      
      }
        // Pequeno delay para evitar loop contínuo
   }
}

