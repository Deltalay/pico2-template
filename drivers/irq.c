#include "../header/irq.h"
#include "../header/reg.h"
#if defined(ARCH_ARM)

void irq_enable(rp2350_irq_t interrupt) {
  if (interrupt < 32) {
    NVIC_ISER0 = (1u << interrupt);
  } else {
    NVIC_ISER1 = (1u << (interrupt - 32));
  }
}

void irq_disable(rp2350_irq_t interrupt) {
  if (interrupt < 32) {
    NVIC_ICER0 = (1u << interrupt);
  } else {
    NVIC_ICER1 = (1u << (interrupt - 32));
  }
}

void irq_set_pending(rp2350_irq_t interrupt) {
  if (interrupt < 32) {
    NVIC_ISPR0 = (1u << interrupt);
  } else {
    NVIC_ISPR1 = (1u << (interrupt - 32));
  }
}

void irq_clear_pending(rp2350_irq_t interrupt) {
  if (interrupt < 32) {
    NVIC_ICPR0 = (1u << interrupt);
  } else {
    NVIC_ICPR1 = (1u << (interrupt - 32));
  }
}

uint8_t irq_pending(rp2350_irq_t interrupt) {
  if (interrupt < 32) {
    return (NVIC_ISPR0 & (1u << interrupt)) != 0;
  } else {
    return (NVIC_ISPR1 & (1u << (interrupt - 32))) != 0;
  }
}

void irq_global_enable(void) { __asm volatile("cpsie i" : : : "memory"); }

void irq_global_disable(void) { __asm volatile("cpsid i" : : : "memory"); }
#elif defined(ARCH_RISCV)

#else

#error "UNKNOWN ARCH"

#endif
