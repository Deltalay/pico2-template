
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
typedef enum { LOW = 0, HIGH = 1 } rp2350_pin_state_t;
typedef enum {
  GPIO_JTAG = 0,
  GPIO_SPI = 1,
  GPIO_UART = 2,
  GPIO_I2C = 3,
  GPIO_PWM = 4,
  GPIO_SIO = 5,
  GPIO_PIO0 = 6,
  GPIO_PIO1 = 7,
  GPIO_PIO2 = 8,
  GPIO_NULL = 0x1F,
} rp2350_gpio_func_t;
typedef enum {
  GPIO_INPUT = 0,
  GPIO_OUTPUT = 1,
  GPIO_IN_OUT = 2,
} rp2350_gpio_direction_t;
void gpio_init(uint8_t pin_number, rp2350_gpio_func_t function);
void gpio_set(uint8_t pin_number, rp2350_gpio_direction_t direction);
void gpio_out(uint8_t pin_number, rp2350_pin_state_t state);
rp2350_pin_state_t gpio_read(uint8_t pin_number);

#endif
