cmake_minimum_required(VERSION 3.15)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(RP2350_BareMetal C ASM)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(TARGET_NAME template)

set(SOURCE
    src/start.c
    src/timer.c
    src/gpio.c
    src/pwm.c
    arch/arm/vector_table.S
    arch/arm/startup.S
)

set(COMMON_FLAGS "-mcpu=cortex-m33 -mthumb -ffreestanding")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${COMMON_FLAGS}")

add_executable(${TARGET_NAME} ${SOURCE})
target_compile_options(${TARGET_NAME} PRIVATE
    -Os
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
    -Wshadow
    -Wundef
)
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
