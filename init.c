
#include "header/start.h"
#include <stdint.h>
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
void Default_Handler(void) {
  while (1) {
  }
}
void Reset_Handler(void) {
  uint32_t *src, *dst;
  src = &_sidata;
  dst = &_sdata;
  while (dst < &_edata) {
    *dst++ = *src++;
  }
  dst = &_sbss;
  while (dst < &_ebss) {
    *dst++ = 0;
  }
  _start();

  while (1) {
  }
}
extern unsigned int _estack;

__attribute__((section(".vectors"))) const void *vector_table[] = {
    &_estack,
    Reset_Handler,
    Default_Handler, 
    Default_Handler,
    Default_Handler,
    Default_Handler, 
    Default_Handler, 
    Default_Handler, 
    0,
    0,
    0,           
    Default_Handler, 
    0,              
    0,              
    Default_Handler,
    Default_Handler, 
};
