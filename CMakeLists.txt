cmake_minimum_required(VERSION 3.14)
project(audioDSP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

set(APP_SRCS
    src/Main.cpp
    src/Player.cpp
    src/DSP.cpp
    src/AudioUtils.cpp
    src/Math.cpp
    src/FIR.cpp
)

set(TEST_SRCS
    tests/Math_test.cpp
    src/Player.cpp
    src/DSP.cpp
    src/AudioUtils.cpp
    src/Math.cpp
    src/FIR.cpp
)

add_executable(app ${APP_SRCS})
target_link_libraries(app ${SDL2_LIBRARIES})

enable_testing()

add_executable(tests ${TEST_SRCS})
target_link_libraries(tests ${SDL2_LIBRARIES} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
