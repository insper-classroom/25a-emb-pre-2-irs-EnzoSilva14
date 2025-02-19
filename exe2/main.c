#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN = 28;
const int LED_PIN = 4;
volatile int gbtn_state = 0;

void btn_callback(uint gpio, uint32_t events) {
  gbtn_state = 1;
}

int main() {
  stdio_init_all();
  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);
  gpio_set_irq_enabled_with_callback(
      BTN_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  
  bool led_state = false;
  while (true) {
    if (gbtn_state == 1) {
      gbtn_state = 0;
      led_state = !led_state;
      gpio_put(LED_PIN, led_state);
    }

  }
}
