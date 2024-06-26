set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_CROSSCOMPILING ON)

set(TOOLCHAIN_PREFIX "arm-none-eabi-")


set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc.exe CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}c++.exe CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}as.exe CACHE INTERNAL "ASM Compiler")
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}ld.exe CACHE INTERNAL "Linker Executable")
set(CMAKE_AR ${TOOLCHAIN_PREFIX}ar.exe CACHE INTERNAL "Library Manager")
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy.exe CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size.exe CACHE INTERNAL "size tool")
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump.exe CACHE INTERNAL "objdump tool")
set(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}ranlib.exe CACHE INTERNAL "ranlib tool")
set(CMAKE_STRIP ${TOOLCHAIN_PREFIX}strip.exe CACHE INTERNAL "strip tool")


set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)