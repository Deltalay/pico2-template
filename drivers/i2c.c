#include "../header/i2c.h"
#include "../header/reg.h"

void i2c_init(rp2350_i2c_cfg_t *cfg) {
  uint8_t i2c_block = 0;
  // I2C0 Pin is for pin that is divisible by 4
  if (cfg->sda_pin <= 20 && cfg->sda_pin % 4 == 0) {
    // For SCL normally in block 0, it is SDA + 1, thus to check
    // if it on the same block, we just - 1 from it.
    i2c_block = 0;
    RESETS_RESET |= (1 << 4);
    RESETS_RESET &= ~(1 << 4);
    while (!(RESETS_RESET_DONE & (1 << 4))) {
    }
    I2C0_IC_ENABLE &= ~(1 << 0);
  } else {
    i2c_block = 1;
    RESETS_RESET |= (1 << 5);
    RESETS_RESET &= ~(1 << 5);
    while (!(RESETS_RESET_DONE & (1 << 5))) {
    }
    I2C1_IC_ENABLE &= ~(1 << 0);
  }
  if (i2c_block == 0) {
    I2C0_IC_ENABLE = 0;
    if (cfg->operate == SLAVE) {
      I2C0_IC_SAR = cfg->addr;
      I2C0_IC_CON &= ~((1 << 6) | (1 << 0));
    } else {
      I2C0_IC_TAR = cfg->addr;
      I2C0_IC_CON |= ((1 << 6) | (1 << 0));
    }
    switch (cfg->speed) {
    case I2C_SPEED_STANDARD: {
      I2C0_IC_CON &= ~(0b11 << 1);
      I2C0_IC_CON |= (1 << 1);
      I2C0_IC_SS_SCL_HCNT = 795;
      I2C0_IC_SS_SCL_LCNT = 705;
      I2C0_IC_SDA_SETUP = 39;
      break;
    }
    case I2C_SPEED_FAST: {
      I2C0_IC_CON &= ~(0b11 << 1);
      I2C0_IC_CON |= (2 << 1);
      I2C0_IC_FS_SCL_HCNT = 180;
      I2C0_IC_FS_SCL_LCNT = 195;
      I2C0_IC_SDA_SETUP = 16;

      break;
    }
    case I2C_SPEED_FAST_PLUS: {
      I2C0_IC_CON &= ~(0b11 << 1);
      I2C0_IC_CON |= (3 << 1);
      I2C0_IC_FS_SCL_HCNT = 132;
      I2C0_IC_FS_SCL_LCNT = 18;
      I2C0_IC_SDA_SETUP = 9;

      break;
    }
    }
    I2C0_IC_FS_SPKLEN = 8;
    I2C0_IC_SDA_HOLD = 1;
    I2C0_IC_ENABLE = 1;

  } else {
    I2C1_IC_ENABLE = 0;
    if (cfg->operate == SLAVE) {
      I2C1_IC_SAR = cfg->addr;
      I2C1_IC_CON &= ~((1 << 6) | (1 << 0));
    } else {
      I2C1_IC_TAR = cfg->addr;
      I2C1_IC_CON |= ((1 << 6) | (1 << 0));
    }
    switch (cfg->speed) {
    case I2C_SPEED_STANDARD: {
      I2C1_IC_CON &= ~(0b11 << 1);
      I2C1_IC_CON |= (1 << 1);
      I2C1_IC_SS_SCL_HCNT = 795;
      I2C1_IC_SS_SCL_LCNT = 705;
      I2C1_IC_SDA_SETUP = 39;
      break;
    }
    case I2C_SPEED_FAST: {
      I2C1_IC_CON &= ~(0b11 << 1);
      I2C1_IC_CON |= (2 << 1);
      I2C1_IC_FS_SCL_HCNT = 180;
      I2C1_IC_FS_SCL_LCNT = 195;
      I2C1_IC_SDA_SETUP = 16;

      break;
    }
    case I2C_SPEED_FAST_PLUS: {
      I2C1_IC_CON &= ~(0b11 << 1);
      I2C1_IC_CON |= (3 << 1);
      I2C1_IC_FS_SCL_HCNT = 132;
      I2C1_IC_FS_SCL_LCNT = 18;
      I2C1_IC_SDA_SETUP = 9;

      break;
    }
    }
    I2C1_FS_SPKLEN = 8;
    I2C1_IC_SDA_HOLD = 1;
    I2C1_IC_ENABLE = 1;
  }
}
void i2c_master_write(rp2350_i2c_cfg_t *cfg, const uint8_t *data,
                      uint16_t data_len) {
  if (cfg->sda_pin <= 20 && cfg->sda_pin % 4 == 0) {
    for (uint16_t i = 0; i < data_len; i++) {
      // Wait WHILE the TX FIFO is full (TFNF == 0)
      while (!(I2C0_IC_STATUS & (1 << 1))) {
      }
      uint32_t value = data[i];
      if (i == data_len - 1) {
        value |= (1 << 9); // STOP on last byte
      }
      I2C0_IC_DATA_CMD = value;
    }
  } else {
    for (uint16_t i = 0; i < data_len; i++) {
      while (!(I2C1_IC_STATUS & (1 << 1))) {
      }
      uint32_t value = data[i];
      if (i == data_len - 1) {
        value |= (1 << 9);
      }
      I2C1_IC_DATA_CMD = value;
    }
  }
}
void i2c_master_read(rp2350_i2c_cfg_t *cfg, uint8_t *dst, uint16_t len) {
  if (cfg->sda_pin <= 20 && cfg->sda_pin % 4 == 0) {
    for (uint16_t i = 0; i < len; i++) {

      while (!(I2C0_IC_STATUS & (1 << 1))) {
      }
      uint32_t cmd = (1 << 8);
      if (i == len - 1) {
        cmd |= (1 << 9);
      }
      I2C0_IC_DATA_CMD = cmd;

      while (!(I2C0_IC_STATUS & (1 << 3))) {
      }
      dst[i] = (uint8_t)(I2C0_IC_DATA_CMD & 0xFF);
    }
  } else {
    for (uint16_t i = 0; i < len; i++) {

      while (!(I2C1_IC_STATUS & (1 << 1))) {
      }
      uint32_t cmd = (1 << 8);
      if (i == len - 1) {
        cmd |= (1 << 9);
      }
      I2C1_IC_DATA_CMD = cmd;

      while (!(I2C1_IC_STATUS & (1 << 3))) {
      }
      dst[i] = (uint8_t)(I2C1_IC_DATA_CMD & 0xFF);
    }
  }
}
