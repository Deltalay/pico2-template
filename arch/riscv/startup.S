.global Reset_Handler
.extern _estack0
.global Default_Handler
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern _start0
.extern init
.extern _start1
.p2align 2
.equ sio_base, 0xd0000000
.equ cpu_id_offset, 0x00
.equ fifo_st_offset, 0x050
.equ fifo_wr_offset, 0x054
.equ fifo_rd_offset, 0x058
.macro VEC name:req
.p2align 2
j \name
.p2align 2
.endm
.section .vectors, "ax"
.p2align 2
.global vector_table
vector_table:
    VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
	VEC Default_Handler
.section .init
.type Reset_Handler, @function
Reset_Handler:
    la sp, _estack0
    la t0, vector_table
    ori t0, t0, 1
    csrw mtvec, t0
    la t0, _sidata
    la t1, _sdata
    la t2, _edata
1:
    bge t1, t2, 2f
    lw t3, 0(t0)
    sw t3, 0(t1)
    addi t0, t0, 4
    addi t1, t1, 4
    j 1b
 2:
    la t1, _sbss
    la t2, _ebss
    li t3, 0
3:  bge t1, t2, 4f
    sw t3, 0(t1)
    addi t1, t1, 4
    j 3b
4:
    call init
    la a0, vector_table
    la a1, _estack1
    la a2, Reset_Handler1
    call Launch_Core1

5:
    call _start0
    j Default_Handler

.section .pico_image_def, "a"
    .align 2
    .word 0xffffded3
    .word 0x11010142
    .word 0x000001ff
    .word 0x00000000
    .word 0xab123579
.section .text
.type Reset_Handler1, @function
Reset_Handler1:
    la t0, vector_table
    ori t0, t0, 1
    csrw mtvec, t0
    call _start1
    j Default_Handler
.type Default_Handler, @function
Default_Handler:
1:
    j 1b
.type Launch_Core1, @function
Launch_Core1:
    addi sp, sp, -24
    sw a0, 12(sp)
    sw a1, 16(sp)
    sw a2, 20(sp)
    li t0, 1
    sw t0, 8(sp)
    sw zero, 4(sp)
    sw zero, 0(sp)
    li t4, sio_base
0:
    li t5, 0
1:
    slli t6, t5, 2
    add t6, sp, t6
    lw t6, 0(t6)
    bnez t6, 3f
2:
    lw t0, fifo_st_offset(t4)
    andi t0, t0, 1
    beqz t0, 3f
    lw t0, fifo_rd_offset(t4)
    slt x0, x0, x1
    j 2b
3:
    lw t0, fifo_st_offset(t4)
    srli t0, t0, 1
    andi t0, t0, 1
    beqz t0, 3b
    sw   t6, fifo_wr_offset(t4)
    slt x0, x0, x1
4:
    lw t0, fifo_st_offset(t4)
    andi t0, t0, 1
    beqz t0, 4b
    lw t0, fifo_rd_offset(t4)
    bne t0, t6, 0b
5:
    addi t5, t5, 1
    li   t0, 6
    blt  t5, t0, 1b
6:
    addi sp, sp, 24         # Clean up stack frame
    ret
