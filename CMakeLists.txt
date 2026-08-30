cmake_minimum_required(VERSION 3.15)
set(ARCH "ARM" CACHE STRING "Switch between ARM and RISC-V")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(CACHE ARCH PROPERTY STRINGS ARM RISCV)
if(ARCH STREQUAL "ARM")
    message(STATUS "Building for ARM")
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
    set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
    set(CMAKE_SIZE arm-none-eabi-size)
    set(SOURCE
        src/start.c
        drivers/timer.c
        drivers/gpio.c
        drivers/usb.c
        drivers/uart.c
        drivers/i2c.c
        drivers/pwm.c
        drivers/irq.c
        arch/arm/startup.S
    )
    set(ARCH_FLAGS
        -mcpu=cortex-m33
        -mthumb
        -ffreestanding
    )
elseif(ARCH STREQUAL "RISCV")
    message(STATUS "Building for RISC-V")
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_PROCESSOR riscv)
    set(CMAKE_C_COMPILER riscv-none-elf-gcc)
    set(CMAKE_ASM_COMPILER riscv-none-elf-gcc)
    set(CMAKE_OBJCOPY riscv-none-elf-objcopy)
    set(CMAKE_SIZE riscv-none-elf-size)
    set(SOURCE
        src/start.c
        drivers/timer.c
        drivers/gpio.c
        drivers/i2c.c
        drivers/usb.c
        drivers/uart.c
        drivers/pwm.c
        drivers/irq.c
        arch/riscv/startup.S
    )
    set(ARCH_FLAGS
        -march=rv32imac_zicsr_zifencei_zba_zbb_zbc_zbs_zbkb
        -mabi=ilp32
        -ffreestanding
    )
else()
    message(FATAL_ERROR "Unknown ARCH: ${ARCH}")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(RP2350_BareMetal C ASM)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(TARGET_NAME template)
add_executable(${TARGET_NAME} ${SOURCE})
target_compile_options(${TARGET_NAME} PRIVATE
    ${ARCH_FLAGS}
    -Os
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
    -Wshadow
    -Wundef
)
if(ARCH STREQUAL "ARM")
    target_compile_definitions(${TARGET_NAME} PRIVATE ARCH_ARM)

elseif(ARCH STREQUAL "RISCV")
    target_compile_definitions(${TARGET_NAME} PRIVATE ARCH_RISCV)
endif()
target_link_options(${TARGET_NAME} PRIVATE
    -nostdlib
    -nostartfiles
    -T ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
    -Wl,-Map=${TARGET_NAME}.map
    -Wl,--gc-sections
)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
            -O binary $<TARGET_FILE:${TARGET_NAME}>
            ${TARGET_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET_NAME}>
    COMMAND picotool uf2 convert
            $<TARGET_FILE:${TARGET_NAME}> ${TARGET_NAME}.uf2

    COMMENT "Generating .bin, printing size, and creating .uf2..."
)
