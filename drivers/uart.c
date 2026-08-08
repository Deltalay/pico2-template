#include "../header/uart.h"
#include "../header/reg.h"
#include <stdint.h>

void uart0_init(uint32_t baudrate) {
  // UART 0
  RESETS_RESET |= (1 << 26);

  RESETS_RESET &= ~(1 << 26);
  while (!(RESETS_RESET_DONE & (1 << 26))) {
  }

  uint32_t div = 4 * UART_CLCK_SYS / baudrate;
  uint32_t ibrd = div >> 6;
  uint32_t fbrd = 0;
  if (ibrd == 0)
    ibrd = 1;
  else if (ibrd >= 65535)
    ibrd = 65535;
  else
    fbrd = div & 0x3f;
  UART0_UARTIBRD &= ~(0xFFFF << 0);
  UART0_UARTFBRD &= ~(0x3F << 0);
  UART0_UARTIBRD |= (ibrd << 0);
  UART0_UARTFBRD |= (fbrd << 0);

}
void uart1_init(uint32_t baudrate) {
  RESETS_RESET |= (1 << 27);
  RESETS_RESET &= ~(1 << 27);
  while (!(RESETS_RESET_DONE & (1 << 27))) {
  }
  uint32_t div = 4 * UART_CLCK_SYS / baudrate;
  uint32_t ibrd = div >> 6;
  uint32_t fbrd = 0;
  if (ibrd == 0)
    ibrd = 1;
  else if (ibrd >= 65535)
    ibrd = 65535;
  else
    fbrd = div & 0x3f;
  UART1_UARTIBRD &= ~(0xFFFF << 0);
  UART1_UARTFBRD &= ~(0x3F << 0);
  UART1_UARTIBRD |= (ibrd << 0);
  UART1_UARTFBRD |= (fbrd << 0);
}
void uart_set(
    uint8_t gpio
) {
    *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + gpio * 0x8u + 0x4) &=
        ~(0x1F << 0);
    *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + gpio * 0x8u + 0x4) |=
        (0x02 << 0);
    volatile uint32_t *pad =
        (volatile uint32_t *)((uintptr_t)PADS_BANK0_BASE + gpio * 0x4 + 0x4);
    *pad |= (3 << 4);
    *pad |= (1 << 3);
    *pad &= ~(1 << 2);
    *pad &= ~(1 << 8);
}
