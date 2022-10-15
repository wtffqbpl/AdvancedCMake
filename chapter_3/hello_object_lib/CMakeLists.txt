# Sometimes, you may want to split off code so that parts of it can be reused without the need
# to create a full-blown library. A common practice is when you want to use some code in an
# executable and unit tests, without the need to recompile everything twice.
# For this, CMake provides object libraries, where the sources are compiled, but not archived
# or linked. An object library is created by calling add_library(MyLibrary OBJECT)
# This object library can be added by target_link_libraries functions since 3.12.
# Before v3.12, object libraries needed to be added with a generator expression; that is
# $<TARGET_OBJECTS:MyLibrary>. This expands to a list of objects during build system generation.
# but it is no longer recommended as it quickly becomes unmaintainable, especially if there are
# multiple object libraries in a project.

project(
        ch3_hello_object_lib
        VERSION 1.0
        DESCRIPTION "Chapter 3 hello object library example"
        LANGUAGES CXX)

add_library(hello_obj_lib OBJECT)
target_sources(hello_obj_lib PRIVATE src/main.cc)