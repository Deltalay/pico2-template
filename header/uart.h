#ifndef UART_H
#define UART_H
#define UART_CLCK_SYS 150000000
#include <stdint.h>
void uart1_init(uint32_t baudrate);
void uart0_init(uint32_t baudrate);
void uart_set(uint8_t pin);
void uart0_put(char c);
void uart0_puts(const char* text);
void uart1_put(char c);
void uart1_puts(const char* text);
#endif
