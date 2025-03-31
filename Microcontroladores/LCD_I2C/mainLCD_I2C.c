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

#use delay(clock=6000000)

#use i2c(Master,Fast=100000, sda=PIN_C4, scl=PIN_C3,force_sw)  
#include "i2c_Flex_LCD.c"  

void main() {  
   int i=0; 
   lcd_init(0x4E,16,2);
   lcd_backlight_led(ON); //Enciende la luz de Fondo
     
 while (TRUE) { 
   lcd_clear();  //Limpia el LCD

   // Envio de Strings al LCD usando la funci�n printf
   printf(lcd_putc, "\fSuscribete a"); 
   delay_ms(1000); 
   printf(lcd_putc, "\nControl      "); 
   delay_ms(1000); 
   printf(lcd_putc, "\nAutomatico    "); 
   delay_ms(1000); 
   printf(lcd_putc, "\nEducacion     "); 
   delay_ms(1000); 

   printf(lcd_putc, "\fAprende:"); 
   delay_ms(1000); 
   printf(lcd_putc, "\n- PIC"); 
   delay_ms(1000); 
   printf(lcd_putc, "\n- Arduino"); 
   delay_ms(1000); 
   printf(lcd_putc, "\n- Control"); 
   delay_ms(1000); 

   // Limpia el LCD 
   printf(lcd_putc, "\f"); 
   delay_ms(500); 

   //Funci�n: lcd_gotoxy()
   //Si colocan un gotoxy mayor al del LCD usado, la propia funci�n
   //internamente coloca los l�mites correctos. A modo de ejemplo
   //coloquemos las esquinas correspondientes a un LCD 20x4 y la funci�n
   //Loa adaptar� si se usa un LCD 16x2

   lcd_gotoxy(3, 1);        
   printf(lcd_putc, "Numeros en");    
   lcd_gotoxy(4, 2);        
   printf(lcd_putc, "Esquinas"); 
   delay_ms(500); 
   lcd_gotoxy(1, 1);        
   printf(lcd_putc, "1"); 
   delay_ms(500); 
   lcd_gotoxy(20, 1);        
   printf(lcd_putc, "2"); 
   delay_ms(500); 
   lcd_gotoxy(20, 4);        
   printf(lcd_putc, "3"); 
   delay_ms(500); 
   lcd_gotoxy(1, 4);        
   printf(lcd_putc, "4");    
   delay_ms(2000); 
   

   // Prueba de la funci�n de borrado Backspace
   printf(lcd_putc, "\f �Suscribete!\n"); 
   printf(lcd_putc,   "Activa: CAMPANA"); 
   delay_ms(2000); 

   // Ultima columna y fila  2
   //Borro la fila 2 con back space
   lcd_gotoxy(20, 2);        

   // Backspace over 2nd line. 
   for(i = 0; i < lcd_total_columns; i++) 
      { 
       printf(lcd_putc," \b\b"); 
       delay_ms(100); 
      } 

   printf(lcd_putc,   " es GRATIS!!!!!!");  
   delay_ms(3000); 

//Apaga Luz de Fondo 
         lcd_backlight_led(OFF); 
         printf(LCD_PUTC,"\fLCD BackLight\n     OFF      "); 
         delay_ms(3000); 

//Enciende Luz de Fondo
         lcd_backlight_led(ON); 
         printf(LCD_PUTC,"\fLCD BackLight\n     ON      ");  
         delay_ms(3000); 

   }    
}
