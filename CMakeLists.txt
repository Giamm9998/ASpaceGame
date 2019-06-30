cmake_minimum_required(VERSION 3.14)
project(ASpaceGame)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML COMPONENTS graphics REQUIRED)
find_package(SFML COMPONENTS window REQUIRED)
find_package(SFML COMPONENTS audio REQUIRED)

add_subdirectory(test)
set(SOURCE_FILES Game.cpp Game.h ResourceManager.cpp ResourceManager.h)
add_executable(ASpaceGame main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-graphics sfml-window sfml-audio)
target_link_libraries(ASpaceGame core)