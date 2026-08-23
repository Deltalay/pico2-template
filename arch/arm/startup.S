.syntax unified
.cpu cortex-m33
.thumb
.global Reset_Handler
.global _estack0
.global _estack1
.global Default_Handler
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern _start0
.extern init
.extern _start1
.extern usbctrl_irq
.equ sio_base, 0xd0000000
.equ cpu_id_offset, 0x00
.equ fifo_st_offset, 0x050
.equ fifo_wr_offset, 0x054
.equ fifo_rd_offset, 0x058
.section .pico_image_def, "a"
.word 0xffffded3
.word 0x10210142
.word 0x000001ff
.word 0x00000000
.word 0xab123579
.section .vectors, "a", %progbits
.type vector_table, %object
.align 9
vector_table:
    .word _estack0
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word MemManage_Handler
    .word BusFault_Handler
    .word UsageFault_Handler
    .word SecureFault_Handler
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word DebugMonitor_Handler
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler
    /* RP2350 IRQ */
    .word TIMER0_IRQ_0
    .word TIMER0_IRQ_1
    .word TIMER0_IRQ_2
    .word TIMER0_IRQ_3
    .word TIMER1_IRQ_0
    .word TIMER1_IRQ_1
    .word TIMER1_IRQ_2
    .word TIMER1_IRQ_3
    .word PWM_IRQ_WRAP_0
    .word PWM_IRQ_WRAP_1
    .word DMA_IRQ_0
    .word DMA_IRQ_1
    .word DMA_IRQ_2
    .word DMA_IRQ_3
    .word USBCTRL_IRQ
    .word PIO0_IRQ_0
    .word PIO0_IRQ_1
    .word PIO1_IRQ_0
    .word PIO1_IRQ_1
    .word PIO2_IRQ_0
    .word PIO2_IRQ_1
    .word IO_IRQ_BANK0
    .word IO_IRQ_BANK0_NS
    .word IO_IRQ_QSPI
    .word IO_IRQ_QSPI_NS
    .word SIO_IRQ_FIFO
    .word SIO_IRQ_BELL
    .word SIO_IRQ_FIFO_NS
    .word SIO_IRQ_BELL_NS
    .word SIO_IRQ_MTIMECMP
    .word CLOCKS_IRQ
    .word SPI0_IRQ
    .word SPI1_IRQ
    .word UART0_IRQ
    .word UART1_IRQ
    .word ADC_IRQ_FIFO
    .word I2C0_IRQ
    .word I2C1_IRQ
    .word OTP_IRQ
    .word TRNG_IRQ
    .word PROC0_IRQ_CTI
    .word PROC1_IRQ_CTI
    .word PLL_SYS_IRQ
    .word PLL_USB_IRQ
    .word POWMAN_IRQ_POW
    .word POWMAN_IRQ_TIMER
    .word SPAREIRQ_IRQ_0
    .word SPAREIRQ_IRQ_1
    .word SPAREIRQ_IRQ_2
    .word SPAREIRQ_IRQ_3
    .word SPAREIRQ_IRQ_4
    .word SPAREIRQ_IRQ_5
    .weak      NMI_Handler
    .thumb_set NMI_Handler,Default_Handler

    .weak      HardFault_Handler
    .thumb_set HardFault_Handler,Default_Handler

    .weak      MemManage_Handler
    .thumb_set MemManage_Handler,Default_Handler

    .weak      BusFault_Handler
    .thumb_set BusFault_Handler,Default_Handler

    .weak      UsageFault_Handler
    .thumb_set UsageFault_Handler,Default_Handler

    .weak      SecureFault_Handler
    .thumb_set SecureFault_Handler,Default_Handler

    .weak      SVC_Handler
    .thumb_set SVC_Handler,Default_Handler

    .weak      DebugMonitor_Handler
    .thumb_set DebugMonitor_Handler,Default_Handler

    .weak      PendSV_Handler
    .thumb_set PendSV_Handler,Default_Handler

    .weak      SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler

    .weak      TIMER0_IRQ_0
    .thumb_set TIMER0_IRQ_0,Default_Handler

    .weak      TIMER0_IRQ_1
    .thumb_set TIMER0_IRQ_1,Default_Handler

    .weak      TIMER0_IRQ_2
    .thumb_set TIMER0_IRQ_2,Default_Handler

    .weak      TIMER0_IRQ_3
    .thumb_set TIMER0_IRQ_3,Default_Handler

    .weak      TIMER1_IRQ_0
    .thumb_set TIMER1_IRQ_0,Default_Handler

    .weak      TIMER1_IRQ_1
    .thumb_set TIMER1_IRQ_1,Default_Handler

    .weak      TIMER1_IRQ_2
    .thumb_set TIMER1_IRQ_2,Default_Handler

    .weak      TIMER1_IRQ_3
    .thumb_set TIMER1_IRQ_3,Default_Handler

    .weak      PWM_IRQ_WRAP_0
    .thumb_set PWM_IRQ_WRAP_0,Default_Handler

    .weak      PWM_IRQ_WRAP_1
    .thumb_set PWM_IRQ_WRAP_1,Default_Handler

    .weak      DMA_IRQ_0
    .thumb_set DMA_IRQ_0,Default_Handler

    .weak      DMA_IRQ_1
    .thumb_set DMA_IRQ_1,Default_Handler

    .weak      DMA_IRQ_2
    .thumb_set DMA_IRQ_2,Default_Handler

    .weak      DMA_IRQ_3
    .thumb_set DMA_IRQ_3,Default_Handler

    .weak      USBCTRL_IRQ
    .thumb_set USBCTRL_IRQ,Default_Handler

    .weak      PIO0_IRQ_0
    .thumb_set PIO0_IRQ_0,Default_Handler

    .weak      PIO0_IRQ_1
    .thumb_set PIO0_IRQ_1,Default_Handler

    .weak      PIO1_IRQ_0
    .thumb_set PIO1_IRQ_0,Default_Handler

    .weak      PIO1_IRQ_1
    .thumb_set PIO1_IRQ_1,Default_Handler

    .weak      PIO2_IRQ_0
    .thumb_set PIO2_IRQ_0,Default_Handler

    .weak      PIO2_IRQ_1
    .thumb_set PIO2_IRQ_1,Default_Handler

    .weak      IO_IRQ_BANK0
    .thumb_set IO_IRQ_BANK0,Default_Handler

    .weak      IO_IRQ_BANK0_NS
    .thumb_set IO_IRQ_BANK0_NS,Default_Handler

    .weak      IO_IRQ_QSPI
    .thumb_set IO_IRQ_QSPI,Default_Handler

    .weak      IO_IRQ_QSPI_NS
    .thumb_set IO_IRQ_QSPI_NS,Default_Handler

    .weak      SIO_IRQ_FIFO
    .thumb_set SIO_IRQ_FIFO,Default_Handler

    .weak      SIO_IRQ_BELL
    .thumb_set SIO_IRQ_BELL,Default_Handler

    .weak      SIO_IRQ_FIFO_NS
    .thumb_set SIO_IRQ_FIFO_NS,Default_Handler

    .weak      SIO_IRQ_BELL_NS
    .thumb_set SIO_IRQ_BELL_NS,Default_Handler

    .weak      SIO_IRQ_MTIMECMP
    .thumb_set SIO_IRQ_MTIMECMP,Default_Handler

    .weak      CLOCKS_IRQ
    .thumb_set CLOCKS_IRQ,Default_Handler

    .weak      SPI0_IRQ
    .thumb_set SPI0_IRQ,Default_Handler

    .weak      SPI1_IRQ
    .thumb_set SPI1_IRQ,Default_Handler

    .weak      UART0_IRQ
    .thumb_set UART0_IRQ,Default_Handler

    .weak      UART1_IRQ
    .thumb_set UART1_IRQ,Default_Handler

    .weak      ADC_IRQ_FIFO
    .thumb_set ADC_IRQ_FIFO,Default_Handler

    .weak      I2C0_IRQ
    .thumb_set I2C0_IRQ,Default_Handler

    .weak      I2C1_IRQ
    .thumb_set I2C1_IRQ,Default_Handler

    .weak      OTP_IRQ
    .thumb_set OTP_IRQ,Default_Handler

    .weak      TRNG_IRQ
    .thumb_set TRNG_IRQ,Default_Handler

    .weak      PROC0_IRQ_CTI
    .thumb_set PROC0_IRQ_CTI,Default_Handler

    .weak      PROC1_IRQ_CTI
    .thumb_set PROC1_IRQ_CTI,Default_Handler

    .weak      PLL_SYS_IRQ
    .thumb_set PLL_SYS_IRQ,Default_Handler

    .weak      PLL_USB_IRQ
    .thumb_set PLL_USB_IRQ,Default_Handler

    .weak      POWMAN_IRQ_POW
    .thumb_set POWMAN_IRQ_POW,Default_Handler

    .weak      POWMAN_IRQ_TIMER
    .thumb_set POWMAN_IRQ_TIMER,Default_Handler

    .weak      SPAREIRQ_IRQ_0
    .thumb_set SPAREIRQ_IRQ_0,Default_Handler

    .weak      SPAREIRQ_IRQ_1
    .thumb_set SPAREIRQ_IRQ_1,Default_Handler

    .weak      SPAREIRQ_IRQ_2
    .thumb_set SPAREIRQ_IRQ_2,Default_Handler

    .weak      SPAREIRQ_IRQ_3
    .thumb_set SPAREIRQ_IRQ_3,Default_Handler

    .weak      SPAREIRQ_IRQ_4
    .thumb_set SPAREIRQ_IRQ_4,Default_Handler

    .weak      SPAREIRQ_IRQ_5
    .thumb_set SPAREIRQ_IRQ_5,Default_Handler




.section .text
.type Reset_Handler, %function
.thumb_func
Reset_Handler:
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
1:
    cmp r1, r2
    bcs 2f
    ldr r3, [r0], #4
    str r3, [r1], #4
    b 1b
2:
    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0
3:
    cmp r1, r2
    bcs 4f
    str r3, [r1], #4
    b 3b

4:
    ldr r0, =vector_table
    ldr r1, =0xE000ED08
    str r0, [r1]
    bl init
    ldr r0, =vector_table
    ldr r1, =_estack1
    ldr r2, =_start1
    bl Launch_Core1
5:
    bl _start0
    b Default_Handler
.type Default_Handler, %function
Default_Handler:
1:
    b 1b
.type Launch_Core1, %function
.thumb_func
Launch_Core1:
    push {r4-r7, lr}
    movs r3, #1
    orrs r2, r2, r3
    push {r2}
    push {r1}
    push {r0}
    movs r3, #1
    push {r3}
    movs r3, #0
    push {r3}
    push {r3}
    ldr r4, =sio_base
0:
    movs r5, #0
1:
    lsls r6, r5, #2
    ldr r6, [sp, r6]
    cmp  r6, #0
    bne  3f
2:
    ldr r0, [r4, #fifo_st_offset]
    movs r1, #1
    ands r0, r0, r1
    beq 3f
    ldr r0, [r4, #fifo_rd_offset]
    sev
    b 2b
3:
    ldr r0, [r4, #fifo_st_offset]
    lsrs r0, r0, #1
    movs r1, #1
    ands r0, r0, r1
    beq 3b
    str  r6, [r4, #fifo_wr_offset]
    sev
4:
    ldr r0, [r4, #fifo_st_offset]
    movs r1, #1
    ands r0, r0, r1
    beq 4b
    ldr r0, [r4, #fifo_rd_offset]
    cmp r0, r6
    bne 0b
5:
    adds r5, #1
    cmp  r5, #6
    blt  1b
6:
    add  sp, sp, #24
    pop  {r4-r7, pc}
