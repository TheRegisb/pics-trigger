cmake_minimum_required(VERSION 3.1)

project(pics-trigger)
set (pics-trigger_VERSION_MAJOR 0)
set (pics-trigger_VERSION_MINOR 1)

include_directories(${CMAKE_SOURCE_DIR}/inc)

set(SOURCES src/main.cpp)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(pics-trigger ${SOURCES})
target_link_libraries(pics-trigger sfml-graphics)
