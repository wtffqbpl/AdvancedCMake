cmake_minimum_required(VERSION 3.21)

project(
        ch3.hello_lib
        VERSION 1.0
        DESCRIPTION "A simple C++ project to demonstrate creating executables and libraries in CMAKE"
        LANGUAGES CXX)

add_library(hello SHARED)
# If the type of the library is omitted, the BUILD_SHARED_LIBS variable determines
# whether the libraries are built as shared or static libraries by default. This
# variable should not be set unconditionally in the CMake files of a project; it
# should always be passed by the user.

target_sources(
        hello
        PRIVATE src/hello.cc
)
# The sources for the libraries are added with target_sources. The sources
# separated by the PRIVATE, PUBLIC, or INTERFACE keyword. In practice, source
# files are almost always added with the PRIVATE specifier.
# The PRIVATE and PUBLIC keywords specify where the sources should be used
# for compiling.
# PRIVATE --- means that the sources will only be used in the target
#             hello itself.
# PUBLIC --- the sources will be added to hello and any target that links to
#            hello. PUBLIC is not usually desired.
# INTERFACE --- which means that the sources are not added to hello but should
#               be added to anything that links against hello.

# Naming libraries
# When you're creating libraries using add_library(<name>), the name of the
# library must be globally unique inside the project as name collisions are
# errors. By default, the actual filename of the library is constructed
# according to the conventions on the platform, such as lib<name>.so on Linux
# and <name>.lib or <name>.dll on Windows. The name of the file can be changed
# from the default behavior by setting the OUTPUT_NAME property of a target.

target_compile_features(hello PUBLIC cxx_std_17)

target_include_directories(
        hello
        PRIVATE src
        PUBLIC include
)

# change target name by using OUTPUT_NAME
set_target_properties(
        hello
        PROPERTIES VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Another convention that's often seen in projects is adding a different postfix to the
# filename for the various build configurations. CMake handles this by setting the
# CMAKE_<CONFIG>_POSTFIX global variable to whatever the convention is or adding the
# <CONFIG>_POSTFIX property to the targets.
# If this variable is set, the postfix will be automatically added to non-executable targets.
# As with most global variables, they should be passed to CMake over the command line or
# as a preset rather than hardcoded in the CMakeLists.txt file.

# 例如, 给debug模式下的lib 文件增加 d 字段的后缀
set_target_properties(
        hello
        PROPERTIES DEBUG_POSTFIX d)

# Changing the default visibility
# To change the default visibility of the symbols,
# set the <LANG>_VISIBILITY_PRESET property to HIDDEN. This property can be set either globally or
# for a single library target.
# <LANG> is substituted for the language that the library is written in, such as CXX for C++
# or C for C. If all the symbols are hidden symbols to be exported, they must be marked
# specially in the code. The most common way to do this is to specify a preprocessor definition
# that determines whether a symbol is visible or not:
#\\\ class HELLO_EXPORT Hello {
#\\\ ...
#\\\ };

# CMake provides the generate_export_header macro, which is imported by the GenerateExportHeader
# module.

set_property(TARGET hello PROPERTY CXX_VISIBILITY_PRESET "hidden")
set_property(TARGET hello PROPERTY VISIBILITY_INLINES_HIDDEN TRUE)
include(GenerateExportHeader)
generate_export_header(hello EXPORT_FILE_NAME export/hello/export_hello.hpp)
target_include_directories(hello PUBLIC "${CMAKE_CURRENT_BINARY_DIR} /export")