#ifndef RESET_H
#define RESET_H
#include <stdint.h>
typedef enum {
  RESET_ADC = 0,
  RESET_BUSCTRL = 1,
  RESET_DMA = 2,
  RESET_HSTX = 3,
  RESET_I2C0 = 4,
  RESET_I2C1 = 5,
  RESET_IO_BANK_0 = 6,
  RESET_IO_QSPI = 7,
  RESET_JTAG = 8,
  RESET_PADS_BANK0 = 9,
  RESET_PADS_QSPI = 10,
  RESET_PIO0 = 11,
  RESET_PIO1 = 12,
  RESET_PIO2 = 13,
  RESET_PLL_SYS = 14,
  RESET_PLL_USB = 15,
  RESET_PWM = 16,
  RESET_SHA256 = 17,
  RESET_SPI0 = 18,
  RESET_SPI1 = 19,
  RESET_SYSCFG = 20,
  RESET_SYSINFO = 21,
  RESET_TBMAN = 22,
  RESET_TIMER0 = 23,
  RESET_TIMER1 = 24,
  RESET_TRNG = 25,
  RESET_UART0 = 26,
  RESET_UART1 = 27,
  RESET_USBCTRL = 28
} rp2350_reset_s_t;
void reset_s(rp2350_reset_s_t reset);
// 1 = reset, 0 = not reset
uint8_t is_reset_s(rp2350_reset_s_t reset);
// take out of reset if haven't
void unreset_s(rp2350_reset_s_t reset);
void wait_until_reset_s_done(rp2350_reset_s_t reset);
// 1 = done reset, 0 not yet
uint8_t is_reset_s_done(rp2350_reset_s_t reset);

#endif
