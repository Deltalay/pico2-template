
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
typedef enum {
    LOW = 0,
    HIGH = 1
} rp2350_pin_state_t;
typedef enum {
    JTAG = 0,
    SPI = 1,
    UART = 2,
    I2C = 3,
    PWM = 4,
    SIO = 5,
    PIO0 = 6,
    PIO1 = 7,
    PIO2 = 8
} rp2350_gpio_func_t;
typedef enum {
    INPUT = 0,
    OUTPUT = 1,
}rp2350_gpio_direction_t;
void gpio_init(uint8_t pin_number, rp2350_gpio_func_t function);
void gpio_set(uint8_t pin_number, rp2350_gpio_direction_t direction);
void gpio_out(uint8_t pin_number, rp2350_pin_state_t state);
rp2350_pin_state_t gpio_read(uint8_t pin_number);

#endif
