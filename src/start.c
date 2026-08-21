#include "../header/pwm.h"
#include "../header/reg.h"
#include "../header/timer.h"
#include "../header/uart.h"
/*
 REFDIV:    1
 FBDIV:     125
 VCO:       1500.0 MHz
 PD1:       5
 PD2:       2
 */
void init() {
  XOSC_CTRL &= ~(0xFFF << 12);
  XOSC_CTRL |= (0xFAB << 12) | 0xAA0;

  while (!(XOSC_STATUS & (1 << 12))) {
  }
  while (!(XOSC_STATUS & (1 << 31))) {
  }
  CLK_REF_CTRL &= ~0x3;
  CLK_REF_CTRL |= 0x2;
  RESETS_RESET &= ~(1 << 14);
  while (!(RESETS_RESET_DONE & (1 << 14))) {
  }
  // PLL_SYS
  PLL_SYS_CS &= ~(0x3F << 0);
  PLL_SYS_CS |= 1; // REFDIV = 1

  PLL_SYS_FBDIV_INT = 125; // FBDIV
  PLL_SYS_PWR &= ~(1 << 0);
  PLL_SYS_PWR &= ~(1 << 5);

  while (!(PLL_SYS_CS & (1 << 31))) {
  }
  PLL_SYS_PRIM &= ~((7 << 16) | (7 << 12));
  PLL_SYS_PRIM |= (5 << 16) | (2 << 12);
  PLL_SYS_PWR &= ~(1 << 3);

  CLK_SYS_CTRL &= ~(7 << 5);
  CLK_SYS_CTRL |= (0 << 5);
  CLK_SYS_CTRL |= (1 << 0);
  CLK_PERI_CTRL &= ~(1 << 11);
  CLK_PERI_CTRL |= (1 << 11);
  CLK_PERI_CTRL &= ~(7 << 5);
  CLK_PERI_CTRL |= (0 << 5);

  TIMER0_SOURCE = 0;
  TICKS_TIMER0_CTRL &= ~1;
  TICKS_TIMER0_CYCLES = 12;
  TICKS_TIMER0_CTRL |= 1;
  while (!(TICKS_TIMER0_CTRL & (1 << 1))) {
  }
}
void enable_fpu() {
#if defined(ARCH_ARM)
  SCB_CPACR |= (0xF << 20); // enable CP10 and CP11
  __asm volatile("dsb");
  __asm volatile("isb");
#elif defined(ARCH_RISCV)

#else
#error "UNKNOWN ARCH"
#endif
}
void _start0(void) {

  enable_fpu();
  uart0_init(115200);
  uart_set(0);
  while (1) {
    uart0_puts("HELLO WORLD");
    delay_s(1);
  }
  // RESETS_RESET &= ~((1u << 6) | (1U << 9));
  // while ((RESETS_RESET_DONE & ((1u << 6) | (1u << 9))) !=
  //        ((1u << 6) | (1u << 9))) {
  // }
  // GPIO25_CTRL &= ~(0x1F);
  // GPIO25_CTRL |= (0x05);
  // PADS_BANK0_GPIO25 |= (3 << 4);
  // PADS_BANK0_GPIO25 |= (1 << 2);
  // PADS_BANK0_GPIO25 &= ~(1 << 8);
  // SIO_GPIO_OE_SET = (1 << 25);
  // SIO_GPIO_OUT_XOR = (1 << 25);
  // while (1) {
  //   delay_s(2);
  //   SIO_GPIO_OUT_XOR = (1 << 25);
  // }
}
void _start1(void) {
  enable_fpu();
  pwm_init();
  pwm_set(25);
  uint8_t percentage = 0;
  int8_t direction = 1;
  while (1) {
    pwm_duty(25, percentage);
    percentage += direction;

    if (percentage == 100) {
      direction = -1;
    } else if (percentage == 0) {
      direction = 1;
    }

    delay_ms(20);
  }
}
