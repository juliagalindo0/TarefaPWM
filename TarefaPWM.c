#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22      // Pino de controle PWM
#define PWM_FREQUENCY 50  // Frequência do PWM em Hz
#define CLOCK_DIV 125.0f  // Divisor de clock para 50Hz
#define TOP_VALUE 40000   // Valor máximo do contador PWM

#define SERVO_MIN 500     // Pulso correspondente a 0 graus (500us)
#define SERVO_MID 1470    // Pulso correspondente a 90 graus (1470us)
#define SERVO_MAX 2400    // Pulso correspondente a 180 graus (2400us)
#define STEP_SIZE 5       // Incremento para suavizar o movimento
#define STEP_DELAY 10     // Tempo de atraso entre mudanças (ms)

void configurar_pwm(uint pino) {
    gpio_set_function(pino, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pino);
    pwm_set_clkdiv(slice, CLOCK_DIV);
    pwm_set_wrap(slice, TOP_VALUE);
    pwm_set_enabled(slice, true);
}

void definir_pulso_pwm(uint pino, uint32_t pulso) {
    pwm_set_gpio_level(pino, pulso);
}

int main() {
    stdio_init_all();
    configurar_pwm(SERVO_PIN);

    // Posicionar servo nos ângulos especificados
    definir_pulso_pwm(SERVO_PIN, SERVO_MAX);
    sleep_ms(5000);
    definir_pulso_pwm(SERVO_PIN, SERVO_MID);
    sleep_ms(5000);
    definir_pulso_pwm(SERVO_PIN, SERVO_MIN);
    sleep_ms(5000);

    uint32_t angulo = SERVO_MIN;
    bool subindo = true;

    while (true) {
        definir_pulso_pwm(SERVO_PIN, angulo);
        sleep_ms(STEP_DELAY);
        
        // Alterna entre mover o servo para frente e para trás
        if (subindo) {
            angulo += STEP_SIZE;
            if (angulo >= SERVO_MAX) subindo = false;
        } else {
            angulo -= STEP_SIZE;
            if (angulo <= SERVO_MIN) subindo = true;
        }
    }
    return 0;
}
