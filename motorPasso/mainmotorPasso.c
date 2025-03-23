//#include "C:\Micro\motorPasso\mainmotorPasso.h"


#define DIR_PIN PIN_B0 // Pino de dire��o

const int step_sequence[4] = {0x01, 0x02, 0x04, 0x08};

void main() {
    set_tris_b(0x01); // RB0 como entrada, o resto como sa�da
    int step = 0;
    
    while (TRUE) {
        if (input(DIR_PIN)) {
            // Sentido hor�rio
            output_b(step_sequence[step]);
            step = (step + 1) % 4;
        } else {
            // Sentido anti-hor�rio
            output_b(step_sequence[step]);
            step = (step - 1 + 4) % 4;
        }
        delay_ms(50); // Delay para 30 RPM (ajuste conforme necess�rio)
    }
}

