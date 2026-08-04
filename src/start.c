#include "../header/reg.h"
void _start(void) {
  RESETS_RESET &= ~((1u << 6) | (1U << 9));
  while ((RESETS_RESET_DONE & ((1u << 6) | (1u << 9))) !=
         ((1u << 6) | (1u << 9))) {
  }
  GPIO25_CTRL &= ~(0x1F);
  GPIO25_CTRL |= (0x05);
  PADS_BANK0_GPIO25 |= (3 << 4);
  PADS_BANK0_GPIO25 |= (1 << 2);
  PADS_BANK0_GPIO25 &= ~(1 << 8);
  SIO_GPIO_OE_SET = (1 << 25);
  SIO_GPIO_OUT_XOR = (1 << 25);
  while (1) {
      for (volatile int i = 0; i < 100000; i++) {
      }
      SIO_GPIO_OUT_XOR = (1 << 25);
  }
}

