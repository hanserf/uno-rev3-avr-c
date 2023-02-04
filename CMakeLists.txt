# I target a recent cmake, it shouldn't be a problem on a dev machine
cmake_minimum_required(VERSION 3.11)
# Project name
project("avr_tmpctrl" C ASM)

# Product filename
set(PRODUCT_NAME IdealCondition)

## AVR Chip Configuration
# 16Mhz, this should match the crystal on your board,
# I use 16Mhz and 5.0V 
set(F_CPU 16000000UL)
# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega328p)
# Default Baudrate for UART, read avr include/util/setbaud.h for usage
set(BAUD 57600)
# The programmer to use, read avrdude manual for list
set(PROG_TYPE arduino)
set(DUINO_TTY "/dev/ttyACM0")
set(DUDE_MCU ATMEGA328P)
# AVR Fuses, must be in concordance with your hardware and F_CPU
# https://forum.arduino.cc/t/standard-fuse-settings-for-16mhz-atmega328p/70962/3
set(E_FUSE 0xFD)
set(H_FUSE 0xDE)
set(L_FUSE 0xFF)
set(LOCK_BIT 0xFF)


# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)


# Pass defines to compiler
add_definitions(
    -DDEBUG
    -DF_CPU=${F_CPU}
    -DBAUD=${BAUD}
    -D__mega328P__
)
# mmcu MUST be passed to bot the compiler and linker, this handle the linker
set(LINKER_OPTS "-Wl,--start-group -lm \
                -Wl,--end-group \
                -Wl,-Map=${PRODUCT_NAME}.map \
                -Wl,--gc-sections -mmcu=atmega328p "
)
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_OPTS}" CACHE STRING "" FORCE)

add_compile_options(
    -c
    -mmcu=${MCU} # MCU
    -std=gnu99 # C99 standard
    -Os # optimize
    -Wall # enable warnings
    -Wno-main
    -Wundef
    -pedantic
    #-Wstrict-prototypes #(void) not () for 0 args
    -Werror
    -Wfatal-errors
    -Wl,--relax,--gc-sections
    -g3
    -gdwarf-2
    -funsigned-char # a few optimizations
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    -fno-split-wide-types
    -fno-tree-scev-cprop
    -B ${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/gcc/dev/atmega328p
    -L ${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/gcc/dev/atmega328p/avr5
    #-l:libatmega328p.a 
    -specs=${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/gcc/dev/atmega328p/device-specs/specs-atmega328p
)
# ASSEMBLER OPTIONS — appended to COMPILE_OPTS
set(ASSEMBLER_OPTS
    -x assembler-with-cpp
)
string(REPLACE ";" "" ASSEMBLER_OPTS_STRING "${ASSEMBLER_OPTS}")
set(CMAKE_ASM_FLAGS "${ASSEMBLER_OPTS_STRING}" CACHE STRING "" FORCE)
# Load all files in bsp folder and application main
set(BSP_SRC_FILES 
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/adc_basic.c" 
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/examples/src/nvmctrl_basic_example.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/wdt.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/tc16.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/examples/src/pwm_basic_example.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/usart_basic.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/nvmctrl_basic.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/examples/src/usart_basic_example.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/ac.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/pwm_basic.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/examples/src/i2c_master_example.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/i2c_types.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/examples/src/spi_basic_example.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/i2c_master.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/driver_init.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/driver_isr.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/i2c_simple_master.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/examples/src/adc_basic_example.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/spi_basic.c"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/atmel_start.c"
    #"${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/gcc/dev/atmega328p/avr5/crtatmega328p.o"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/gcc/dev/atmega328p/avr5/libatmega328p.a"
    ) 

set(BSP_HEADERS
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/config"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/examples/include"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/include"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/utils"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/utils/assembler"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/include"
    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/include/avr"
)

# Application sources
set(SRC_FILES 
    "main.c"
    "src/my_printf.c"
)
set(INCLUDE_HEADERS
    "inc"
)


# Create one target
add_executable(${PRODUCT_NAME}
                "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/src/protected_io.S" 
                ${SRC_FILES}
                ${BSP_SRC_FILES}
              )
# Include headers
target_include_directories(${PRODUCT_NAME}
    PUBLIC
    ${BSP_HEADERS}
    ${INCLUDE_HEADERS}
)


#target_link_libraries(${PRODUCT_NAME} 
#    #libatmega328p.a
#    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/gcc/dev/atmega328p/avr5/crtatmega328p.o"
#    "${CMAKE_SOURCE_DIR}/Uno_rev3_bsp/gcc/dev/atmega328p/avr5/libatmega328p.a"
#)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)
add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Strip binary for upload
add_custom_target(bin ALL avr-objcopy -O binary ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.bin DEPENDS strip)

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS bin)
# Transform binary into hex file, this is the eeprom part (empty if you don't
# use eeprom static variables)
add_custom_target(eeprom avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS hex)

add_custom_target(lss avr-objdump -h -S ${PRODUCT_NAME}.elf > ${PRODUCT_NAME}.lst DEPENDS eeprom)
add_custom_target(size avr-size ${PRODUCT_NAME}.elf lss)

# Flash the firmware with avrdude
#add_custom_target(flash avrdude -v -c ${PROG_TYPE} -P ${DUINO_TTY} -p ${MCU} -b 57600 -D -U flash:w:${PRODUCT_NAME}.hex DEPENDS lss)
add_custom_target(flash avrdude -v avrdude -F -V -D -c ${PROG_TYPE} -P ${DUINO_TTY} -p ${DUDE_MCU} -b 115200 -U flash:w:${PRODUCT_NAME}.elf DEPENDS lss)

# Flash the eeprom with avrdude
add_custom_target(flash_eeprom avrdude -F -V -c ${PROG_TYPE} -P ${DUINO_TTY} -p ${DUDE_MCU} -b 115200 -U eeprom:w:${PRODUCT_NAME}.eep DEPENDS eeprom)

# Burn fuses
add_custom_target(fuses avrdude -F -V -c ${PROG_TYPE} -P ${DUINO_TTY} -p ${DUDE_MCU} -b 115200 -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m )

# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst")

