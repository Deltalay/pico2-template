.syntax unified
.cpu cortex-m33
.thumb
.global Reset_Handler
.global _estack
.global Default_Handler
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern _start
.section .vectors, "a", %progbits
.type vector_table, %object
vector_table:
    .word _estack
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

.section .text
.thumb
.type Reset_Handler, %function
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
    bl _start
.type Default_Handler, %function
Default_Handler:
1:
    b 1b
