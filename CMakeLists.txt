cmake_minimum_required(VERSION 3.21)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("AdvancedCMake"
        VERSION 1.0
        DESCRIPTION "My Advanced CMake Learning materials."
        LANGUAGES CXX)

add_subdirectory(chapter_1)
add_subdirectory(chapter_2)
add_subdirectory(chapter_3)