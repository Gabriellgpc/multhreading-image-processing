cmake_minimum_required(VERSION 3.15)
project(Multithreading)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
# General warning flags for both Debug and Release
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(single single.cpp)
target_link_libraries(single ${OpenCV_LIBS})

add_executable(multi multi.cpp)
target_link_libraries(multi ${OpenCV_LIBS} OpenMP::OpenMP_CXX)