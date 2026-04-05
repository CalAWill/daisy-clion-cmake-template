cmake_minimum_required(VERSION 3.16)

# --- Project Setup ---
project(DaisyTemplate C CXX ASM)

# --- Daisy Hardware Configuration ---
# SD Card support
set(USE_FATFS ON CACHE BOOL "Enable FatFS" FORCE)
set(USE_SDMMC ON CACHE BOOL "Enable SDMMC" FORCE)

# --- Dependencies ---
add_subdirectory(lib/libDaisy)
add_subdirectory(lib/DaisySP)

# --- Executable Configuration ---
# Automatically find and compile any .cpp file you put in the src/ folder
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        daisy
        DaisySP
)

# --- Linker Settings ---
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/lib/libDaisy/core/STM32H750IB_flash.lds)

target_link_options(${PROJECT_NAME}
    PUBLIC
        -T${LINKER_SCRIPT}
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
)

# --- Post-Build Binary Generation ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
    COMMENT "Generating .hex and .bin files"
)

# --- Flash Target (USB DFU) ---
add_custom_target(FlashDaisy
    COMMAND dfu-util -a 0 -s 0x08000000:leave -D ${PROJECT_NAME}.bin -d ,0483:df11
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Flashing Daisy Seed via USB DFU..."
)
