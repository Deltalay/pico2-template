#include "../header/reset.h"
#include "../header/reg.h"

void unreset_s(rp2350_reset_s_t reset) {
  hw_clear_bits(RESETS_RESET, 1U << reset);
}
uint8_t is_reset_s(rp2350_reset_s_t reset) {
  return (RESETS_RESET >> reset) & 0b1;
}
void reset_s(rp2350_reset_s_t reset) {
  hw_set_bits(RESETS_RESET, 1U << reset);
};
void wait_until_reset_s_done(rp2350_reset_s_t reset) {
  while (!is_reset_s_done(reset)) {
  }
}
uint8_t is_reset_s_done(rp2350_reset_s_t reset) {
  return (RESETS_RESET_DONE >> reset) & 0b1;
};
