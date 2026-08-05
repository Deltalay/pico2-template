#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
uint64_t get_time(void);
void delay_ms(uint32_t ms);
void delay_us(uint64_t us);
void delay_s(uint32_t s);
#endif
