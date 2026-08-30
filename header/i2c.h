#ifndef I2C_H
#define I2C_H
#include "stdint.h"
typedef enum {
  I2C_SPEED_STANDARD = 100000,
  I2C_SPEED_FAST = 400000,
  I2C_SPEED_FAST_PLUS = 1000000
} rp2350_i2c_speed_t;
typedef enum {
  MASTER,
  SLAVE,
} rp2350_i2c_operate_t;
typedef struct {
  uint16_t addr;
  rp2350_i2c_speed_t speed;
  uint8_t sda_pin;
  uint8_t scl_pin;
  rp2350_i2c_operate_t operate;
} rp2350_i2c_cfg_t;
void i2c_init(rp2350_i2c_cfg_t *cfg);
void i2c_master_write(rp2350_i2c_cfg_t *cfg, const uint8_t *data,
                      uint16_t data_len);
void i2c_master_read(rp2350_i2c_cfg_t *cfg, uint8_t *dst, uint16_t len);
#endif
