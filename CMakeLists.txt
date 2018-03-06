cmake_minimum_required (VERSION 3.5)
project(BoxingTimer)













include_directories(${PROJECT_ROOT}/include)
project(BoxingTimer)
set (CMAKE_CXX_STANDARD 11)
include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(BoxingTimer src/main.cpp src/Timer.cpp src/Timer.h)

