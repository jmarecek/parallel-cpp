cmake_minimum_required(VERSION 3.5)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_OSX_ARCHITECTURES x86_64)

set(CMAKE_CXX_STANDARD 20) # or 23 from CMAKE 3.20
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(code_examples LANGUAGES CXX)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -I/usr/local/opt/tbb/include")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS} -L/usr/local/opt/tbb/lib -ltbb")
endif()

set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-but-set-variable -pedantic -fsanitize=address,undefined")

set(CMAKE_VERBOSE_MAKEFILE OFF)

add_subdirectory(introduction)
add_subdirectory(cpp23)
add_subdirectory(openmp)
# add_subdirectory(sycl)
# add_subdirectory(algorithms)