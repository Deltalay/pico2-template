#ifndef PWM_H
#define PWM_H
#include <stdint.h>
#define CLK_SYS_SPEED 150000000
void pwm_init(void);
void pwm_duty(uint8_t gpio, uint8_t duty_percentage);
void pwm_set(uint8_t gpio);
#endif
