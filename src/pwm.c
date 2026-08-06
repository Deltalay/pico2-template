#include "../header/pwm.h"
#include "../header/reg.h"
void pwm_init() {
  // set pwm to 0
  RESETS_RESET &= ~(1 << 16);
  // wait til pwm done reset
  while (!(RESETS_RESET_DONE & (1 << 16))) {
  };
}
void pwm_pin(uint8_t gpio)
{
    
}