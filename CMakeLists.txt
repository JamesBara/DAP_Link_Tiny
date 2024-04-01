cmake_minimum_required (VERSION 3.25.1)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(DAP_Link_Tiny LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
#enable_language(C)

add_compile_options(
        -mcpu=cortex-m4
        -std=gnu11
        -c
        -ggdb3
        -Og #0g or 03
        -Wall
        -Wextra
        -Wpedantic
        -fstack-usage
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -mthumb
        -ffunction-sections
        -fdata-sections
        )

set(DEBUG true)

#Evaluate all definition options.
set(LIST_COMPILE_DEFINITIONS)

if (NOT DEBUG)
    list(APPEND LIST_COMPILE_DEFINITIONS NDEBUG)
endif()

add_compile_definitions(
    ${LIST_COMPILE_DEFINITIONS}
        )

set(LINKER_FILE ${PROJECT_SOURCE_DIR}/stm32l412.ld)

set(SRC_FILES
        ${PROJECT_SOURCE_DIR}/Src/rcc.c
        ${PROJECT_SOURCE_DIR}/Src/usbd.c
        ${PROJECT_SOURCE_DIR}/Src/SW_DP.c
        ${PROJECT_SOURCE_DIR}/Src/DAP.c
        ${PROJECT_SOURCE_DIR}/Src/DAP_vendor.c
        main.c
        )

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  SUFFIX .elf
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/Inc
        )



add_subdirectory(stm32l412_system)


target_link_libraries(${PROJECT_NAME} PUBLIC
    stm32l412_system
        )

# Linker options
target_link_options(${PROJECT_NAME} PRIVATE
        -mcpu=cortex-m4
        -T${LINKER_FILE}        
        -static
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -mthumb
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        -ffreestanding
        -Xlinker -print-memory-usage
        )

        



add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        VERBATIM
        COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
        COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
        COMMAND ${CMAKE_OBJDUMP} -h ${PROJECT_NAME}.elf
        )

