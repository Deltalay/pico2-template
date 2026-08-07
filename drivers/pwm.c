#include "../header/pwm.h"
#include "../header/reg.h"
#define TOP_VALUE 65534
void pwm_init() {
  // set pwm to 0
  RESETS_RESET &= ~(1 << 16);
  RESETS_RESET &= ~(1U << 9);
  // wait til pwm done reset
  while (!(RESETS_RESET_DONE & (1 << 16))) {
  };
  while (!(RESETS_RESET_DONE & (1 << 9))) {
  };
}
void pwm_duty(uint8_t gpio, uint8_t duty_percentage) {
  uint16_t duty_translate = (uint32_t)duty_percentage * TOP_VALUE / 100;
  uint8_t slice;
  uint8_t channel_type; // 0 = A, 1 = B

  channel_type = gpio & 1;

  if (gpio < 32) {
    slice = (gpio >> 1) & 0x07;
  } else {
    slice = 8 + (((gpio - 32) >> 1) & 0x03);
  }
  volatile uint32_t *csr =
      (volatile uint32_t *)((uintptr_t)PWM_BASE + slice * 0x14);
  // we use default div, which is 1
  // uint32_t div =
  //     *(volatile uint32_t *)((uintptr_t)PWM_BASE + slice * 0x14 + 0x4);
  // for this, we also don't need it for now.
  // uint32_t ctr =
  //     *(volatile uint32_t *)((uintptr_t)PWM_BASE + slice * 0x14 + 0x8);

  volatile uint32_t *cc =
      (volatile uint32_t *)((uintptr_t)PWM_BASE + slice * 0x14 + 0xc);

  if (channel_type) {
    *cc &= ~(0xFFFF << 16);
    *cc |= ((uint32_t)duty_translate << 16);
  } else {
    *cc &= ~(0xFFFF << 0);
    *cc |= ((uint32_t)duty_translate << 0);
  }
  *csr |= (1u << 0);
}
void pwm_set(uint8_t gpio) {
  uint8_t slice;

  if (gpio < 32) {
    slice = (gpio >> 1) & 0x07;
  } else {
    slice = 8 + (((gpio - 32) >> 1) & 0x03);
  }
  // GPIOx_CTRL
  *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + gpio * 0x8u + 0x4) &=
      ~(0x1F << 0);
  *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + gpio * 0x8u + 0x4) |=
      (0x04 << 0);
  volatile uint32_t *top =
      (volatile uint32_t *)((uintptr_t)PWM_BASE + slice * 0x14 + 0x10);
  *top &= ~(0xFFFFu);
  *top |= TOP_VALUE;
  volatile uint32_t *pad =
      (volatile uint32_t *)((uintptr_t)PADS_BANK0_BASE + gpio * 0x4 + 0x4);
  *pad |= (3 << 4);
  *pad |= (1 << 2);
  *pad &= ~(1 << 8);
}
