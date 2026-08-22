MEMORY
{
    FLASH(rx) : ORIGIN = 0x10000000, LENGTH = 0x1000000
    RAM(rwx)  : ORIGIN = 0x20000000, LENGTH = 0x82000
}

_flash_base = ORIGIN(FLASH);

_estack0 = ORIGIN(RAM) + LENGTH(RAM);
_estack1 = ORIGIN(RAM) + LENGTH(RAM) - 0x1000;

SECTIONS
{
    .init :
    {
        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);

        KEEP(*(.vectors))
        KEEP(*(.pico_image_def))
        *(.text .text*)
        *(.rodata .rodata*)
        *(.srodata .srodata*)

        . = ALIGN(4);
    } > FLASH

    .data :
    {
        . = ALIGN(4);

        _sdata = .;

        *(.data .data.*)
        *(.sdata .sdata.*)

        . = ALIGN(4);

        _edata = .;
    } > RAM AT > FLASH

    _sidata = LOADADDR(.data);

    .bss :
    {
        . = ALIGN(4);

        _sbss = .;

        *(.sbss .sbss.*)
        *(.bss .bss.*)
        *(COMMON)

        . = ALIGN(4);

        _ebss = .;
    } > RAM
}