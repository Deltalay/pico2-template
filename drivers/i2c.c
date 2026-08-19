#include "../header/i2c.h"
#include "../header/reg.h"
#include <assert.h>

void i2c_init(uint8_t sda_pin, uint8_t scl_pin, enum i2c_speed speed) {
  uint8_t i2c_block = 0;
  // I2C0 Pin is for pin that is divisible by 4
  if (sda_pin <= 20 && sda_pin % 4 == 0) {
    // For SCL normally in block 0, it is SDA + 1, thus to check
    // if it on the same block, we just - 1 from it.
    assert((scl_pin - 1) % 4);
    RESETS_RESET |= (1 << 4);
    RESETS_RESET &= ~(1 << 4);
    while (!(RESETS_RESET_DONE & (1 << 4))) {
    }
  } else {
    i2c_block = 1;
    RESETS_RESET |= (1 << 5);
    RESETS_RESET &= ~(1 << 5);
    while (!(RESETS_RESET_DONE & (1 << 5))) {
    }
  }
  uint8_t pad0_reset_val = (RESETS_RESET >> 9) & 1;
  uint8_t io_bank0_reset_val = (RESETS_RESET >> 6) & 1;
  // RESET VALUE IS 1
  if (pad0_reset_val == 1) {
    RESETS_RESET |= (1 << 9);
    RESETS_RESET &= ~(1 << 9);
    while (!(RESETS_RESET_DONE & (1 << 9))) {
    }
  }
  if (io_bank0_reset_val == 1) {
    RESETS_RESET |= (1 << 6);
    RESETS_RESET &= ~(1 << 6);
    while (!(RESETS_RESET_DONE & (1 << 6))) {
    }
  }
  *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + sda_pin * 0x8u + 0x4) &=
      ~(0x1F << 0);
  *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + sda_pin * 0x8u + 0x4) |=
      (0x03 << 0);
  *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + scl_pin * 0x8u + 0x4) &=
      ~(0x1F << 0);
  *(volatile uint32_t *)((uintptr_t)IO_BANK0_BASE + scl_pin * 0x8u + 0x4) |=
      (0x03 << 0);
  volatile uint32_t *pad_sda =
      (volatile uint32_t *)((uintptr_t)PADS_BANK0_BASE + sda_pin * 0x4 + 0x4);
  volatile uint32_t *pad_scl =
      (volatile uint32_t *)((uintptr_t)PADS_BANK0_BASE + scl_pin * 0x4 + 0x4);
  *pad_sda |= (3 << 4);
  *pad_sda |= (1 << 3);
  *pad_sda &= ~(1 << 2);
  *pad_sda &= ~(1 << 8);
  *pad_scl |= (3 << 4);
  *pad_scl |= (1 << 3);
  *pad_scl &= ~(1 << 2);
  *pad_scl &= ~(1 << 8);
  switch (speed) {
  case I2C_SPEED_STANDARD: {
    if (i2c_block == 0) {
      I2C0_IC_CON &= (0b11 << 1);
      I2C0_IC_CON |= (0b1 << 1);
      break;
    }
    I2C1_IC_CON &= (0b11 << 1);
    I2C1_IC_CON |= (0b1 << 1);
    break;
  }
  // According to reference manual, both Fast and Fast plus is 0x2
  case I2C_SPEED_FAST:
  case I2C_SPEED_FAST_PLUS:
    if (i2c_block == 0) {
      I2C0_IC_CON &= (0b11 << 1);
      I2C0_IC_CON |= (0b10 << 1);
      break;
    }
    I2C1_IC_CON &= (0b11 << 1);
    I2C1_IC_CON |= (0b10 << 1);
    break;
  // Default to standard speed, since it is upward compatible.
  default:
    if (i2c_block == 0) {
      I2C0_IC_CON &= (0b11 << 1);
      I2C0_IC_CON |= (0b1 << 1);
      break;
    }
    I2C1_IC_CON &= (0b11 << 1);
    I2C1_IC_CON |= (0b1 << 1);
    break;
  }
}
