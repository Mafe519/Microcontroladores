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
   #define lcd_enable     pin_E1    // pino enable do LCD
   #define lcd_rs         pin_E2    // pino rs do LCD
   //#define lcd_rw         pin_A4    // pino rw do LCD
   #define lcd_d4         pin_d4    // pino de dados d4 do LCD
   #define lcd_d5         pin_d5    // pino de dados d5 do LCD
   #define lcd_d6         pin_d6    // pino de dados d6 do LCD
   #define lcd_d7         pin_d7    // pino de dados d7 do LCD
#endif

#include "mod_lcd.c"

signed int8 incr = 1;

#int_EXT
void  EXT_isr(void) 
{
   incr = incr * (-1);
}

unsigned int16 tempo = 0;
unsigned int16 valor = 0;
unsigned int8 posicao[4] = {1, 2, 4, 8};
signed int8 passo = 0;

#int_TIMER1
void  TIMER1_isr(void) 
{
   tempo++;
   if(tempo >= valor) {
      
      passo = passo + incr;
      if(passo > 3)passo = 0;
      if(passo < 0)passo = 3;
      
      output_D(posicao[passo] & 0x0F);
      
      tempo = 0;
   }
   set_timer1(60536);
}

unsigned int8 angulo[3] = {0, 90, 180};
signed int8 posicao_servo = 0;
unsigned int16 pulso[3] = {800, 1500, 2200};

void Rotation(int8 pos) //Servo Motor
   {
   unsigned int i;
   for(i=0;i<100;i++)
      {
         output_high(PIN_B4);
         delay_us(pulso[pos]);
         output_low(PIN_B4);
         delay_us(22000-pulso[pos]);
         }
    }

void main()
{
   
   // configuração do AD
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_16);
   
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);

   ext_int_edge( L_TO_H );

   lcd_ini();
   delay_ms(50);
   
   set_adc_channel(0);
   delay_us(50);
   
   lcd_escreve ('\f');  // Apaga (limpa) o display
   printf (lcd_escreve,"   IFMT 2024    \r\n");
   printf (lcd_escreve,"    MOTORES    ");
   delay_ms (2000);
   
   while(true){ 
      valor = read_adc();
      
      printf(lcd_escreve,"\fangulo = %u\n\r", angulo[posicao_servo]);
      printf(lcd_escreve,"sentido = %d", incr);
      
      Rotation(posicao_servo);
      posicao_servo++;
      if(posicao_servo > 2) { 
         posicao_servo = 0;
      }
   }
}
