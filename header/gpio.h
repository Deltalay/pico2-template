
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
typedef enum {
  ENM_NORMAL = 0x0,
  ENM_INVERT = 0x1,
  ENM_LOW = 0x2,
  ENM_HIGH = 0x03,
} rp2350_gpio_ctrl_s_t;
typedef enum {
  DRIVE_2MA = 0x0,
  DRIVE_4MA = 0x1,
  DRIVE_8MA = 0x2,
  DRIVE_12MA = 0x3
} rp2350_gpio_drive_t;
typedef enum {
  GPIO_PULL_NONE,
  GPIO_PULL_UP,
  GPIO_PULL_DOWN,
  GPIO_PULL_BOTH,
} rp2350_gpio_pull_mode_t;
typedef enum {
  GPIO_SLEW_SLOW = 0,
  GPIO_SLEW_FAST = 1,
} rp2350_gpio_slew_t;
typedef enum {
  GPIO_SCHMITT_DISABLE = 0,
  GPIO_SCHMITT_ENABLE = 1,
} rp2350_gpio_schmitt_t;
typedef enum {
  GPIO_ISO_DISABLE = 0,
  GPIO_ISO_ENABLE = 1,
} rp2350_gpio_iso_t;
typedef struct {
  uint8_t pin_number;
  rp2350_gpio_direction_t direction;
  rp2350_gpio_func_t function;
  rp2350_gpio_ctrl_s_t irq_over;
  rp2350_gpio_ctrl_s_t in_over;
  rp2350_gpio_ctrl_s_t oe_over;
  rp2350_gpio_ctrl_s_t out_over;
  rp2350_gpio_drive_t drive;
  rp2350_gpio_pull_mode_t pull_mode;
  rp2350_gpio_slew_t slew_rate;
  rp2350_gpio_schmitt_t schmitt;
  rp2350_gpio_iso_t iso;
} rp2350_gpio_t;
void gpio_init(rp2350_gpio_t *gpio);
void gpio_out(uint8_t pin_number, rp2350_pin_state_t state);
rp2350_pin_state_t gpio_read(uint8_t pin_number);

#endif
