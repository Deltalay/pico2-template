#include "../header/gpio.h"
#include "../header/reg.h"
#include <stdint.h>
void gpio_init(uint8_t pin_number, rp2350_gpio_func_t function) {
  // IO_BANK0 and PADS_BANK0, 1 = reset sate, 0 = non reset state
  // we only take it out of reset if it haven't.
  // and after we take it out, we will wait until it reset successfully
  if (RESETS_RESET & (1 << 6)) {
    RESETS_RESET &= ~(1 << 6);
    while (!(RESETS_RESET_DONE & (1 << 6))) {
    }
  }
  if (RESETS_RESET & (1 << 9)) {
    RESETS_RESET &= ~(1 << 9);
    while (!(RESETS_RESET_DONE & (1 << 9))) {
    }
  }

  volatile uint32_t *pad = (volatile uint32_t *)((uintptr_t)PADS_BANK0_BASE +
                                                 pin_number * 0x4 + 0x4);
  // 12MA, PULL UP, Disable PULL down, disable ISO
  *pad &= ~(3 << 4);
  *pad |= (3 << 4);
  *pad |= (1 << 3);
  *pad &= ~(1 << 2);
  *pad &= ~(1 << 8);
  volatile uint32_t *io =
      (volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + pin_number * 0x8u + 0x4);
  *io &= ~(0x1F << 0);
  *io |= (function << 0);
}
void gpio_set(uint8_t pin_number, rp2350_gpio_direction_t direction) {
  // 1/0 -> ouput/input
  volatile uint32_t *pad = (volatile uint32_t *)((uintptr_t)PADS_BANK0_BASE +
                                                 pin_number * 0x4 + 0x4);

  if (direction == INPUT) {
    // Enable INput and output disable
    *pad |= (1 << 6);
    *pad |= (1 << 7);
    SIO_GPIO_OE_CLR = 1 << pin_number;
    return;
  }
  // Disable input and disable output disable.
  *pad &= ~(1 << 6);
  *pad &= ~(1 << 7);
  SIO_GPIO_OE_SET = 1 << pin_number;
}
void gpio_out(uint8_t pin_number, rp2350_pin_state_t state) {
  // For clr, and set it is WO.
  if (state == LOW) {
    SIO_GPIO_OUT_CLR = 1 << pin_number;
    return;
  }
  SIO_GPIO_OUT_SET = 1 << pin_number;
}
rp2350_pin_state_t gpio_read(uint8_t pin_number) {
  return (SIO_GPIO_IN >> pin_number) & 0b1;
}
