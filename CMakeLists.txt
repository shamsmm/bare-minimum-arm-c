cmake_minimum_required(VERSION 3.10)

project(c0 C ASM)

include_directories(${PROJECT_SOURCE_DIR}/inc)
file(GLOB C_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")
file(GLOB ASM_SOURCES "${PROJECT_SOURCE_DIR}/src/*.s")

add_executable(c0 ${C_SOURCES} ${ASM_SOURCES})