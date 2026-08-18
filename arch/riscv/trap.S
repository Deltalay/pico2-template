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
.equ SIO_BASE,       0xD0000000
.equ FIFO_ST_OFFSET, 0x050
.equ FIFO_WR_OFFSET, 0x054
.equ FIFO_RD_OFFSET, 0x058
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
    # la a0, vector_table
    # la a1, _estack1
    # la a2, _start1
    # call Launch_Core1

5:
    call _start1
    j Default_Handler

.section .text
.type Default_Handler, @function
Default_Handler:
1:
    j 1b
.type Launch_Core1, @function
Launch_Core1:
    call Default_Handler
