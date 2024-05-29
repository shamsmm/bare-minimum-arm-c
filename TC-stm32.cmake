# the name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)

# which compilers to use for C and asm
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -mthumb -mcpu=cortex-m3 -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ggdb -mthumb -mcpu=cortex-m3 -O0 -T ${PROJECT_SOURCE_DIR}/linker.ld")

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  /usr/arm-none-eabi/)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)