#include "../header/gpio.h"
#include "../header/reg.h"
#include <stdint.h>
void gpio_init(rp2350_gpio_t *gpio) {
  volatile uint32_t *pad = (volatile uint32_t *)((uintptr_t)PADS_BANK0_BASE +
                                                 gpio->pin_number * 0x4 + 0x4);

  volatile uint32_t *io = (volatile uint32_t *)((uintptr_t)IO_BANK0_BASE +
                                                gpio->pin_number * 0x8u + 0x4);
  hw_clear_bits_ptr(io, (GPIO_NULL << 0));
  hw_set_bits_ptr(io, (gpio->function << 0));
  if (gpio->direction == GPIO_INPUT) {
    hw_set_bits_ptr(pad, 1U << 6);
    hw_set_bits_ptr(pad, 1U << 7);

    if (gpio->pin_number < 32) {
      SIO_GPIO_OE_CLR = 1UL << gpio->pin_number;
    } else {
      SIO_GPIO_HI_OE_CLR = 1U << (gpio->pin_number - 32);
    }

  } else if (gpio->direction == GPIO_OUTPUT) {
    hw_clear_bits_ptr(pad, 1U << 6);
    hw_clear_bits_ptr(pad, 1U << 7);

    if (gpio->pin_number < 32) {
      SIO_GPIO_OE_SET = 1UL << gpio->pin_number;
    } else {
      SIO_GPIO_HI_OE_SET = 1U << (gpio->pin_number - 32);
    }

  } else if (gpio->direction == GPIO_IN_OUT) {
    hw_set_bits_ptr(pad, 1U << 6);
    hw_clear_bits_ptr(pad, 1U << 7);
    if (gpio->pin_number < 32) {
      SIO_GPIO_OE_SET = 1UL << gpio->pin_number;
    } else {
      SIO_GPIO_HI_OE_SET = 1U << (gpio->pin_number - 32);
    }
  }
  hw_clear_bits_ptr(pad, (0b1 << 8));
  hw_set_bits_ptr(pad, (gpio->iso << 8));
  hw_clear_bits_ptr(pad, (0b11 << 4));
  hw_set_bits_ptr(pad, (gpio->drive << 4));
  hw_clear_bits_ptr(pad, (1U << 0));
  hw_set_bits_ptr(pad, (gpio->slew_rate << 0));
  hw_clear_bits_ptr(pad, (1U << 1));
  hw_set_bits_ptr(pad, (gpio->schmitt << 1));
  switch (gpio->pull_mode) {
  case GPIO_PULL_UP:
    // disable pull down, enable pull up
    hw_set_bits_ptr(pad, (1U << 3));
    hw_clear_bits_ptr(pad, (1U << 2));
    break;
  case GPIO_PULL_DOWN:
    hw_clear_bits_ptr(pad, (1U << 3));
    hw_set_bits_ptr(pad, (1U << 2));
    break;
  case GPIO_PULL_BOTH:
    hw_set_bits_ptr(pad, (1U << 3));
    hw_set_bits_ptr(pad, (1U << 2));
    break;
  case GPIO_PULL_NONE:
    hw_clear_bits_ptr(pad, (1U << 3));
    hw_clear_bits_ptr(pad, (1U << 2));
    break;
  }
  hw_clear_bits_ptr(io, (0b11 << 28));
  hw_clear_bits_ptr(io, (0b11 << 16));
  hw_clear_bits_ptr(io, (0b11 << 14));
  hw_clear_bits_ptr(io, (0b11 << 12));

  hw_set_bits_ptr(io, (gpio->irq_over << 28));
  hw_set_bits_ptr(io, (gpio->in_over << 16));
  hw_set_bits_ptr(io, (gpio->oe_over << 14));
  hw_set_bits_ptr(io, (gpio->out_over << 12));
}

void gpio_out(uint8_t pin_number, rp2350_pin_state_t state) {
  // For clr, and set it is WO.
  if (state == LOW) {
    if (pin_number < 32) {
      SIO_GPIO_OUT_CLR = 1UL << pin_number;
    } else {
      SIO_GPIO_HI_OUT_CLR = 1U << (pin_number - 32);
    }
    return;
  }
  if (pin_number < 32) {
    SIO_GPIO_OUT_SET = 1UL << pin_number;
  } else {
    SIO_GPIO_HI_OUT_SET = 1U << (pin_number - 32);
  }
}
rp2350_pin_state_t gpio_read(uint8_t pin_number) {
  if (pin_number < 32) {
    return (SIO_GPIO_IN >> pin_number) & 0b1;
  }

  return (SIO_GPIO_HI_IN >> (pin_number - 32)) & 0b1;
}
