cmake_minimum_required(VERSION 3.14)
project(ASpaceGame)

set(CMAKE_CXX_STANDARD 11)


add_subdirectory(./lib/googletest-master)
set(gtest_SOURCE_DIR, ./lib/googletest-master/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(TEST_SOURCE_FILES RunAllTests.cpp GameTest.cpp PlayerTest.cpp EmenyTest.cpp BackgroundTest.cpp PowerUpTest.cpp)
add_executable(runGameTest ${TEST_SOURCE_FILES})
target_link_libraries(runGameTest gtest gtest_main core)