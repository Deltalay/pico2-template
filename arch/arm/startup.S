.section .init, "a"
.align 4
.word _estack0
.word Reset_Handler

.word 0xffffded3
.word 0x10210142
.word 0x000001ff
.word 0x00000000
.word 0xab123579
