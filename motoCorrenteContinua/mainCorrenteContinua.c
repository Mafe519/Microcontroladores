//#include "C:\Micro\motoCorrenteContinua\mainCorrenteContinua.h"


#define START_PIN PIN_B0
#define STOP_PIN PIN_B1
#define PWM_PIN PIN_C2

void main() {
    setup_ccp1(CCP_PWM); // Configura CCP1 como PWM
    setup_timer_2(T2_DIV_BY_16, 255, 1); // Configura Timer2
    set_tris_b(0x03); // RB0 e RB1 como entrada, o resto como saída
    
    int duty = 0;
    
    while (TRUE) {
        if (input(START_PIN)) {
            // Aumenta o duty cycle gradualmente até 100%
            for (duty = 0; duty <= 1023; duty++) {
                set_pwm1_duty(duty);
                delay_ms(10);
                if (input(STOP_PIN)) {
                    break;
                }
            }
        }
        
        if (input(STOP_PIN)) {
            // Diminui o duty cycle gradualmente até 0%
            for (duty = 1023; duty >= 0; duty--) {
                set_pwm1_duty(duty);
                delay_ms(10);
                if (input(START_PIN)) {
                    break;
                }
            }
        }
    }
}

