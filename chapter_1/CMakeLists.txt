project(
        "chapter1"
        VERSION 1.0
        DESCRIPTION "A simple project to demonstrate basic CMake usage"
        LANGUAGES CXX)

message(STATUS "The current PROJECT_NAME is ${PROJECT_NAME}.")
# The output is(with STATUS keyword):
# -- The current PROJECT_NAME is chapter1.

message("The top level project name is ${CMAKE_PROJECT_NAME}.")
# The output is(no signature):
# The top level project name is AdvancedCMake.

# VARIABLES:
# Variables can be set using the set command and deleted using unset.
# Variable names are case-sensitive.
# define a variable.
set(MYVAR "1 2 3 4")
message(STATUS "MYVAR is ${MYVAR}")
# we can use unset for variable unset.
unset(MYVAR)

# Variable references can even be nested and are evaluated inside out:
# ${outer_${inner_variable}_variable}

# Variable might be scoped in the following way:
# * Function scope: Variables that are set inside a function are only visible
#                   inside the function.
# * Directory scope: Each of the subdirectories in a source tree binds variables
#                    and includes any variable bindings from the parent
#                    directory.
# * Persistent cache: Cached variables can be either system- or user-defined.
#                     These persist their values over multiple runs.

# Passing the PARENT_SCOPE option to set() makes the variable visible in the
# parent scope.
# Ref:  https://cmake.org/cmake/help/latest/ manual/cmake-variables.7.html.

# LISTS
# CMake stores variables as strings internally. But we can work with lists in
# CMake by splitting values with a semicolon.
# Lists can be created by either passing multiple unquoted variables to set()
# or directly as a semicolon-separated string:
# Eg.
set(MYLIST abc def ghi)
message(STATUS "${MYLIST}")
unset(MYLIST)
# output is: -- abc;def;ghi

set(MYLIST "abc;def;ghi")
message(STATUS "${MYLIST}")
unset(MYLIST)
# output is: -- abc;def;ghi

# Manipulating lists by modifying their contents, reordering, or finding things
# can be done using the list command. The following code will query MYLIST for
# the index of the abc value and then retrieve the value and store it in the
# variable called ABC:
set(MYLIST abc def ghi)
list(FIND MYLIST abc ABC_INDEX)     # get abc index in MYLIST.
list(GET MYLIST ${ABC_INDEX} ABC)   # get string from list by specified index.
message(STATUS "The index is ${ABC_INDEX}, and the value is \"${ABC}\"")
message(STATUS "MYLIST[${ABC_INDEX}] = ${ABC}.")
# OUTPUT:
# -- The index is 0, and the value is "abc"
# -- MYLIST[0] = abc.

# append a value to a list.
list(APPEND MYLIST "xyz")
message(STATUS "MYLIST is ${MYLIST}.")
# Output is: -- MYLIST is abc;def;ghi;xyz.

# Cached variables and options.
# CMake caches some variables so that they run faster in subsequent builds.
# The variables are stored in CMakeCache.txt files. Usually, you don't have
# to edit them manually, but they are great for debugging builds that do not
# behave as expected.
set(ch1_MYVAR foo CACHE STRING "Variable foo that configures bar")
message(STATUS "Cached variable ch1_MYVAR is ${ch1_MYVAR}.")
# output is: -- Cached variable ch1_MYVAR is foo.

# For simple Boolean cache variables, CMake also provides the option keyword.
# option has a default value of OFF unless specified otherwise. They can also
# depend on each other via the CMakeDependentOption module.
# Options are often a convenient way to specify simple project configuration.
# They are cache variables of the bool type. If a variable with the same name
# as the option already exists, a call to option does nothing.
option(CHAPTER1_PRINT_LANGUAGE_EXAMPLES "Print examples for each language" ON)
include(CMakeDependentOption)
# cmake_dependent_option(<OPTION_NAME> "<help_text>" <default_value> <depends> <force_value>)
#   OPTION_NAME --- new option name.
#   help_text   --- helper info.
#   default_value --- default value.
#   depends       --- depends option
cmake_dependent_option(CHAPTER1_PRINT_HELLO_WORLD
        "print a greeting from chapter " ON CHAPTER1_PRINT_LANGUAGE_EXAMPLES OFF)
# If CHAPTER1_PRINT_LANGUAGE_EXAMPLES is ON, then set CHAPTER1_PRINT_HELLO_WORLD
# to OFF. And CHAPTER1_PRINT_HELLO_WORLD's default value is ON.

# FIXME: Why CHAPTER1_PRINT_LANGUAGE_EXAMPLES's value is OFF???
if(CHAPTER1_PRINT_LANGUAGE_EXAMPLES)
    message(STATUS "CHAPTER1_PRINT_LANGUAGE_EXAMPLES option is ON.")
else()
    message(STATUS "CHAPTER1_PRINT_LANGUAGE_EXAMPLES option is OFF.")
endif()
if(CHAPTER1_PRINT_HELLO_WORLD)
    message(STATUS "CHAPTER1_PRINT_HELLO_WORLD option is ON.")
else()
    message(STATUS "CHAPTER1_PRINT_HELLO_WORLD option is OFF.")
endif()

# IMPORTANT: All variables with CMAKE_ prefix are stand for
#            root project information.

# The current project that's being parsed is stored in the PROJECT_NAME variable.
# For the root project, this is also stored in CMAKE_PROJECT_NAME, which is
# useful for determining whether a project is standalone or encapsulated in
# another. Since version 3.21, there's also a PROJECT_IS_TOP_LEVEL variable
# to directly determine whether the current project is the top-level project.

# There are some additional variables regarding the projects.
# And all of them can be prefixed with CMAKE_ to the value for the root project.
# PROJECT_DESCRIPTION
# PROJECT_HOMEPAGE_URL
# PROJECT_VERSION
# PROJECT_VERSION_MAJOR
# PROJECT_VERSION_MINOR
# PROJECT_VERSION_PATCH
# PROJECT_VERSION_TWEAK

add_executable(Chapter1)
target_sources(Chapter1 PRIVATE src/main.cc)