#include "../header/uart.h"
#include "../header/reg.h"
#include <stdint.h>

void uart0_init(uint32_t baudrate) {
  // UART 0
  RESETS_RESET |= (1 << 26);

  RESETS_RESET &= ~(1 << 26);
  while (!(RESETS_RESET_DONE & (1 << 26))) {
  }
  UART0_UARTCR = 0;
  uint64_t div = 4 * UART_CLCK_SYS / baudrate;
  uint32_t ibrd = div >> 6;
  uint32_t fbrd = div & 0x3f;
  if (ibrd == 0) {
    ibrd = 1;
    fbrd = 0;
  } else if (ibrd >= 65535) {
    ibrd = 65535;
    fbrd = 0;
  }
  UART0_UARTIBRD &= ~(0xFFFF << 0);
  UART0_UARTFBRD &= ~(0x3F << 0);
  UART0_UARTIBRD |= (ibrd << 0);
  UART0_UARTFBRD |= (fbrd << 0);
  UART0_UARTLCR_H &= ~(1 << 7);
  UART0_UARTLCR_H &= ~(0b11 << 5);
  UART0_UARTLCR_H |= (0b11 << 5);
  UART0_UARTLCR_H &= ~(0b1111 << 0);
  UART0_UARTLCR_H |= (0b1 << 4);
  UART0_UARTCR |= (0b11 << 8);
  UART0_UARTCR &= ~(0b1 << 0);
  UART0_UARTCR |= (0b1 << 0);
}
void uart1_init(uint32_t baudrate) {
  RESETS_RESET |= (1 << 27);
  RESETS_RESET &= ~(1 << 27);
  while (!(RESETS_RESET_DONE & (1 << 27))) {
  }
  UART1_UARTCR = 0;
  uint64_t div = 4 * UART_CLCK_SYS / baudrate;
  uint32_t ibrd = div >> 6;
  uint32_t fbrd = div & 0x3f;
  if (ibrd == 0) {
    ibrd = 1;
    fbrd = 0;
  } else if (ibrd >= 65535) {
    ibrd = 65535;
    fbrd = 0;
  }
  UART1_UARTIBRD &= ~(0xFFFF << 0);
  UART1_UARTFBRD &= ~(0x3F << 0);
  UART1_UARTIBRD |= (ibrd << 0);
  UART1_UARTFBRD |= (fbrd << 0);
  // Sets UART format to 8N1 with FIFOs enabled
  // (8 data bits, 1 stop bit, no parity, stick parity/break disabled).
  UART1_UARTLCR_H &= ~(1 << 7);
  UART1_UARTLCR_H &= ~(0b11 << 5);
  UART1_UARTLCR_H |= (0b11 << 5);
  UART1_UARTLCR_H &= ~(0b1111 << 0);
  UART1_UARTLCR_H |= (0b1 << 4);
  // This is redundant because the reset already 0b11
  // TXE and RXE
  UART1_UARTCR |= (0b11 << 8);
  UART1_UARTCR &= ~(0b1 << 0);
  UART1_UARTCR |= (0b1 << 0);
}
void uart_set(uint8_t gpio) {
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
uint16_t uart0_reads(uint8_t *data, uint16_t buffer_size) {
  uint16_t i = 0;
  // accomate -1 for \0
  for (i = 0; i < buffer_size - 1; i++) {
    // While 1, fifo is empty so we wait
    data[i] = uart0_read();
    if (data[i] == '\0' || data[i] == '\n' || data[i] == '\r')

      break;
  }
  data[i] = '\0';
  return i;
}
uint8_t uart0_read() {
  while (UART0_UARTFR & (1 << 4)) {
  }
  return UART0_UARTDR & 0xFF;
}
uint8_t uart1_read() {
  while (UART1_UARTFR & (1 << 4)) {
  }
  return UART1_UARTDR & 0xFF;
}
uint16_t uart1_reads(uint8_t *data, uint16_t buffer_size) {
  uint16_t i = 0;
  // accomate -1 for \0
  for (i = 0; i < buffer_size - 1; i++) {
    // While 1, fifo is empty so we wait
    data[i] = uart1_read();
    if (data[i] == '\0' || data[i] == '\n' || data[i] == '\r')

      break;
  }
  data[i] = '\0';
  return i;
}
void uart0_put(uint8_t c) {
  // Trasmit FIFO full, so we will wait
  while (UART0_UARTFR & (1 << 5)) {
  }
  UART0_UARTDR = c;
}
void uart0_puts(const uint8_t *text) {
  while (*text) {
    if (*text == '\n') {
      uart0_put('\r');
    }
    uart0_put(*text++);
  }
}
void uart1_put(uint8_t c) {
  // Trasmit FIFO full, so we will wait
  while (UART1_UARTFR & (1 << 5)) {
  }
  UART1_UARTDR = c;
}
void uart1_puts(const uint8_t *text) {
  while (*text) {
    if (*text == '\n') {
      uart1_put('\r');
    }
    uart1_put(*text++);
  }
}
