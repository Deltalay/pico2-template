#ifndef UART_H
#define UART_H
#define UART_CLCK_SYS 150000000
#include <stdint.h>
void uart1_init(uint32_t baudrate);
void uart0_init(uint32_t baudrate);
void uart_set(uint8_t pin);
void uart0_put(uint8_t c);
void uart0_puts(const uint8_t *text);
void uart1_put(uint8_t c);
void uart1_puts(const uint8_t *text);
uint8_t uart0_read();
uint8_t uart1_read();
uint16_t uart0_reads(uint8_t *data, uint16_t buffer_size);
uint16_t uart1_reads(uint8_t *data, uint16_t buffer_size);

#endif
