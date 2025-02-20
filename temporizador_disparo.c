#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_PIN_1 11  // LED azul
#define LED_PIN_2 12  // LED vermelho
#define LED_PIN_3 13  // LED verde
#define BUTTON_PIN 5  // Botão

enum led_state { ALL_ON, TWO_ON, ONE_ON, ALL_OFF };  // Estados dos LEDs
volatile enum led_state current_state = ALL_OFF;

// Função para habilitar/desabilitar a interrupção do botão
void enable_button_interrupt(bool enable) {
    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, enable);
}

int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    if (current_state == ALL_ON) {
        gpio_put(LED_PIN_1, 0);  // Desliga LED azul
        current_state = TWO_ON;
        return 3000000;  // 3 segundos em microssegundos
    } else if (current_state == TWO_ON) {
        gpio_put(LED_PIN_2, 0);  // Desliga LED vermelho
        current_state = ONE_ON;
        return 3000000;  // 3 segundos em microssegundos
    } else if (current_state == ONE_ON) {
        gpio_put(LED_PIN_3, 0);  // Desliga LED verde
        current_state = ALL_OFF;
        enable_button_interrupt(true);  // Reabilita a interrupção do botão
        return 0;  // Não agendar novo alarme
    } else {
        // Todos os LEDs são ligados novamente
        current_state = ALL_ON;
        gpio_put(LED_PIN_1, 1);  // Liga LED azul
        gpio_put(LED_PIN_2, 1);  // Liga LED vermelho
        gpio_put(LED_PIN_3, 1);  // Liga LED verde
        return 3000000;  // 3 segundos em microssegundos
    }
}

void button_callback(uint gpio, uint32_t events) {
    if (current_state == ALL_OFF) {
        // Inicia a sequência de LEDs ao pressionar o botão
        current_state = ALL_ON;
        gpio_put(LED_PIN_1, 1);  // Liga LED azul
        gpio_put(LED_PIN_2, 1);  // Liga LED vermelho
        gpio_put(LED_PIN_3, 1);  // Liga LED verde
        enable_button_interrupt(false);  // Desabilita a interrupção do botão
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);  // 3 segundos
    }
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs
    gpio_init(LED_PIN_1);
    gpio_set_dir(LED_PIN_1, GPIO_OUT);
    gpio_init(LED_PIN_2);
    gpio_set_dir(LED_PIN_2, GPIO_OUT);
    gpio_init(LED_PIN_3);
    gpio_set_dir(LED_PIN_3, GPIO_OUT);

    // Configuração do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Ativa o pull-up interno

    // Configuração da interrupção do botão
    enable_button_interrupt(true);  // Habilita a interrupção do botão
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, button_callback);

    // Inicializa os LEDs como apagados
    gpio_put(LED_PIN_1, 0);
    gpio_put(LED_PIN_2, 0);
    gpio_put(LED_PIN_3, 0);

    while (true) {
        tight_loop_contents();  // Loop infinito, aguarda as interrupções
    }

    return 0;
}