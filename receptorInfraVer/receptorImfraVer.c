#include <16F877A.h>
#device adc=10

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

#use delay(clock=6000000)


#define IR_INPUT PIN_C2
#define IR_OUTPUT PIN_D0

unsigned int16 ir_width;

#INT_CCP1
void ccp1_isr(void) {
   ir_width = get_timer1();
   clear_interrupt(INT_CCP1);
}

void main() {
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_2); // Configura o timer1 para uma frequência de 1MHz (metade do clock de 6MHz)
   setup_ccp1(CCP_CAPTURE_RE); // Configura CCP1 para captura de borda de subida
   enable_interrupts(INT_CCP1); // Habilita interrupção CCP1
   enable_interrupts(GLOBAL); // Habilita todas as interrupções globais
   
   while(TRUE) {
      // Se um pulso IR foi detectado
      if (ir_width > 1000 && ir_width < 2000) {
         output_low(IR_OUTPUT); // Ligar saída IR
         delay_ms(10); // Aguardar um curto período de tempo
         output_high(IR_OUTPUT); // Desligar saída IR
      }
   }
}
