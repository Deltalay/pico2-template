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
.section .vectors, "a", %progbits
.type vector_table, %object
vector_table:
    .word _estack0
    .word Reset_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler
    .word 0
    .word 0
    .word Default_Handler
    .word Default_Handler
    /* RP2350 IRQ */
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word usbctrl_irq
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler



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
