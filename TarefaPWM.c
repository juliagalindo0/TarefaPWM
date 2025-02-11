#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22      // Pino de controle PWM do servo
#define LED_PIN 12        // Pino do canal azul do LED RGB
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

void configurar_led_pwm(uint pino) {
    gpio_set_function(pino, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pino);
    pwm_set_clkdiv(slice, CLOCK_DIV);
    pwm_set_wrap(slice, TOP_VALUE);
    pwm_set_enabled(slice, true);
}

void definir_intensidade_led(uint pino, uint32_t intensidade) {
    pwm_set_gpio_level(pino, intensidade);
}

int main() {
    stdio_init_all();
    configurar_pwm(SERVO_PIN);
    configurar_led_pwm(LED_PIN);

    // Posicionamento inicial do servo
    definir_pulso_pwm(SERVO_PIN, SERVO_MAX);
    definir_intensidade_led(LED_PIN, TOP_VALUE); // Máxima intensidade de azul
    sleep_ms(5000);

    definir_pulso_pwm(SERVO_PIN, SERVO_MID);
    definir_intensidade_led(LED_PIN, TOP_VALUE / 2); // Intensidade média
    sleep_ms(5000);

    definir_pulso_pwm(SERVO_PIN, SERVO_MIN);
    definir_intensidade_led(LED_PIN, 0); // Azul apagado
    sleep_ms(5000);

    uint32_t angulo = SERVO_MIN;
    bool subindo = true;

    while (true) {
        definir_pulso_pwm(SERVO_PIN, angulo);

        // Ajusta a intensidade do azul conforme o ângulo do servo
        uint32_t intensidade_azul = ((angulo - SERVO_MIN) * TOP_VALUE) / (SERVO_MAX - SERVO_MIN);
        definir_intensidade_led(LED_PIN, intensidade_azul);

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
