cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "prog")
set(LIBPATH "~/lib")

# set compiler
set(CMAKE_C_COMPILER "arm-none-eabi-gcc" CACHE PATH "" FORCE)

# set flags for compilation
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -march=armv7-m -mthumb -mfloat-abi=soft")

# dont use libc because my link script is not compatible (yet TODO)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib")

# target specific flags
set(CMAKE_C_FLAGS_DEBUG "-Og -g -gdwarf-3 -gstrict-dwarf")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# general project settings
project(${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 99)

# enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("Generating Target: ${CMAKE_BUILD_TYPE}")



# --- get all the needed files together ---
# get all header files
include_directories("${LIBPATH}/cmsis_device_f1/Include" "${LIBPATH}/cmsis_core/Include" "include")

# get all c files
file(GLOB APP_SOURCES "*.c")
file(GLOB LIB_SOURCES "src/*.c")



# --- setup cmake for crosscompiling ---
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)

# Try to get around the c compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")



# --- set macros ---
# select chip specific stuff
add_compile_definitions(STM32F103xB)
add_compile_definitions(HSE_VALUE=8000000)

add_library(display ${LIB_SOURCES})



# --- compile uC application and strip some stuff ---
# set linker flags
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-T\"${CMAKE_CURRENT_SOURCE_DIR}/startup.s\"")

# objcopy elf to bin
set(CMAKE_C_OBJCOPY arm-none-eabi-objcopy CACHE PATH "" FORCE)

add_custom_target(firmware.bin ALL DEPENDS firmware.elf)
add_custom_command(TARGET firmware.bin
    COMMAND ${CMAKE_C_OBJCOPY} ARGS -O binary firmware.elf firmware.bin)

# add executable from collected sources
add_executable(firmware.elf ${APP_SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/startup.c")

add_dependencies(firmware.elf display)

target_link_libraries(firmware.elf
    PRIVATE
    display
)
