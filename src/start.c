#include "../header/gpio.h"
#include "../header/reg.h"
#include "../header/reset.h"
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
  PLL_SYS_PRIM = (5 << 16) | (2 << 12);
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
  unreset_s(RESET_IO_BANK_0);
  unreset_s(RESET_PADS_BANK0);
  unreset_s(RESET_UART0);
  wait_until_reset_s_done(RESET_IO_BANK_0);
  wait_until_reset_s_done(RESET_PADS_BANK0);
  wait_until_reset_s_done(RESET_UART0);

  uart0_init(115200);
  rp2350_gpio_t uart_pin = {
      .direction = GPIO_IN_OUT,
      .pin_number = 16,
      .function = GPIO_UART,
      .irq_over = ENM_NORMAL,
      .in_over = ENM_NORMAL,
      .oe_over = ENM_NORMAL,
      .out_over = ENM_NORMAL,
      .drive = DRIVE_12MA,
      .pull_mode = GPIO_PULL_UP,
      .schmitt = GPIO_SCHMITT_DISABLE,
      .slew_rate = GPIO_SLEW_SLOW,
  };
  rp2350_gpio_t uart_pin1 = {
      .direction = GPIO_IN_OUT,
      .pin_number = 17,
      .function = GPIO_UART,
      .irq_over = ENM_NORMAL,
      .in_over = ENM_NORMAL,
      .oe_over = ENM_NORMAL,
      .out_over = ENM_NORMAL,
      .drive = DRIVE_12MA,
      .pull_mode = GPIO_PULL_UP,
      .schmitt = GPIO_SCHMITT_DISABLE,
      .slew_rate = GPIO_SLEW_SLOW,
  };
  gpio_init(&uart_pin);
  gpio_init(&uart_pin1);

  static uint8_t data[1024];
  uint16_t data_size = 1024;
  for (uint16_t i = 0; i < data_size; i++) {
    data[i] = '\0';
  }
  uart0_puts((uint8_t *)"HELLO WORLD");

  while (1) {

    uint16_t rec_size = uart0_reads(data, data_size);
    if (rec_size) {
      uart0_puts(data);
    }
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
  unreset_s(RESET_PADS_BANK0);
  unreset_s(RESET_IO_BANK_0);
  wait_until_reset_s_done(RESET_IO_BANK_0);
  wait_until_reset_s_done(RESET_PADS_BANK0);
  rp2350_gpio_t led_pin = {
      .direction = GPIO_OUTPUT,
      .pin_number = 25,
      .function = GPIO_SIO,
      .irq_over = ENM_NORMAL,
      .in_over = ENM_NORMAL,
      .oe_over = ENM_NORMAL,
      .out_over = ENM_NORMAL,
      .drive = DRIVE_12MA,
      .pull_mode = GPIO_PULL_UP,
      .schmitt = GPIO_SCHMITT_ENABLE,
      .slew_rate = GPIO_SLEW_SLOW,
  };
  gpio_init(&led_pin);
  while (1) {
    gpio_out(25, HIGH);
    delay_ms(200);
    gpio_out(25, LOW);
    delay_ms(200);
  }
}
