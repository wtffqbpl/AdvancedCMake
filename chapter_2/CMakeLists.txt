project(
        "chapter2"
        VERSION 1.0
        DESCRIPTION "CMake file for chapter 2"
        LANGUAGES CXX)
message(STATUS "The current PROJECT_NAME is ${PROJECT_NAME}")

# CMake command:
# cmake -G "Ninja" -S <project_root> -B <output_directory>