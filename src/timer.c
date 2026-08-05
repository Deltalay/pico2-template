#include "../header/timer.h"
#include "../header/reg.h"

uint64_t get_time(void) {
  uint32_t high1, high2, low;

  do {
    high1 = TIMER0_TIMERAWH;
    low = TIMER0_TIMERAWL;
    high2 = TIMER0_TIMERAWH;
  } while (high1 != high2);

  return ((uint64_t)high1 << 32) | low;
}
void delay_us(uint32_t us) {
  uint64_t start = get_time();

  while ((get_time() - start) < us) {
  }
}

void delay_ms(uint32_t ms) { delay_us(ms * 1000); }

void delay_s(uint32_t s) { delay_us(s * 1000000); }
