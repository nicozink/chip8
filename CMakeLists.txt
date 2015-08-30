cmake_minimum_required(VERSION 2.8)

PROJECT(chip8)

# Set user specified flags.
if (MSVC)
set(CMAKE_CXX_FLAGS "")
else ()
set(CMAKE_CXX_FLAGS "-DDEBUG -g -Wall -O0 -std=c++0x")
endif()

set(SRC_MAIN
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chip8_emulator.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_EXECUTABLE(
  chip8
  ${SRC_MAIN})
  
#TARGET_LINK_LIBRARIES(chip8 chip8)
