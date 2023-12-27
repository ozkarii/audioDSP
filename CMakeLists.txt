cmake_minimum_required(VERSION 3.14)
project(audioDSP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})


set(SRCS
    src/Player.cpp
    src/DSP.cpp
    src/AudioUtils.cpp
    src/Main.cpp
    src/Math.cpp
    src/FIR.cpp
)

add_executable(app ${SRCS})
target_link_libraries(app ${SDL2_LIBRARIES})
