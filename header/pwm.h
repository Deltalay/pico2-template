#ifndef PWM_H
#define PWM_H
#include <stdint.h>
#define CLK_SYS_SPEED 150000000
void pwm_init(void);
void pwm_pin(uint8_t gpio);
#endif
