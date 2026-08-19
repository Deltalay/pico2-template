#ifndef I2C_H
#define I2C_H
#include <stdint.h>
#define IC_CLK 150000000
enum i2c_speed {
  I2C_SPEED_STANDARD = 100000,
  I2C_SPEED_FAST = 400000,
  I2C_SPEED_FAST_PLUS = 1000000
};
enum i2c_status {
  I2C_OK = 0,
  I2C_ERR_GENERIC = -1,
  I2C_ERR_TIMEOUT = -2,
  I2C_ERR_ADDR_NACK = -3,
  I2C_ERR_DATA_NACK = -4,
  I2C_ERR_ARB_LOST = -5,
  I2C_ERR_BUS_BUSY = -6,
  I2C_ERR_INVALID_ARG = -7
};

void i2c_init(uint8_t sda_pin, uint8_t scl_pin, enum i2c_speed speed );
#endif
