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

# Properties
# Properties in CMake are values that are attached to a specific object or scope
# of CMake, such as a file, target, directory, or test case. Properties can be
# set or changed by using the set_property function. To read the value of a
# property, you can use the get_property function, which follows a similar
# pattern. By default, set_property overwrites the values that are already
# stored inside a property. Values can be added to the current value by passing
# APPEND or APPEND_STRING to set_property.
# The full signature is as follows:
# set_property(<GLOBAL                      |
#               DIRECTORY [<dir>]           |
#               TARGET [<target1> ...]      |
#               SOURCE [<src1> ...] [DIRECTORY <dirs> ...] [TARGET_DIRECTORY <targets> ...] |
#               INSTALL [<file1> ...]       |
#               TEST [<test1> ...]          |
#               CACHE [<entry1> ...]        |
#               [APPEND] [APPEND_STRING]
#               PROPERTY <propertyName> [<values>])
# **GLOBAL** Global properties that affect the whole build process.
# **DIRECTORY** <dir>: properties that are bound to the current directory or
#        the directories specified in <dir>. These can also be set directly
#        using the set_directory_properties command.
# **TARGET <targets>** Properties of specific targets. They can also be set
#        using the set_target_properties function.
# IMPORTANT:
# It is good practice to use direct functions such as set_target_properties and
# set_test_properties when modifying properties instead of the more general
# set_property command. Using explicit commands avoids making mistakes and
# confusion between the proeprty names and is generally more readable. There's
# also the define_property function, which creates a property without setting
# the value. We advise that you don't use this as properties should always have
# a sane default value.

# Loops and conditions.
set(LoopCnt 0)
while (LoopCnt LESS "5")
    message(STATUS "Chapter1: LoopCnt is '${LoopCnt}'.")
    math(EXPR LoopCnt "${LoopCnt} + 1")
endwhile()
unset(LoopCnt)

# foreach
set(MYLIST abc def ghi)
foreach(ITEM IN LISTS MYLIST)
    # find index
    list(FIND MYLIST ${ITEM} idx)
    message(STATUS "${ITEM} is the ${idx}-th value in MYLIST.")
endforeach()

# Functions
# Functions open a new scope for variables, so all the variables that are
# defined inside are not accessible from the outside unless the PARENT_SCOPE
# option is passed to set().
# Functions are case-insensitive and are invoked by calling function, followed
# by parentheses.
function(foo ARG1)
    message(STATUS "The foo function's argument value is ${ARG1}.")
endfunction()
foo("bar")

# macros
# CMake macros are defined using the macro()/endmacro() commands. They are a
# bit like functions, with the difference that in functions, the arguments are
# true variables, whereas in macros, they are string replacements. This means
# that all arguments of a macro must be accessed using curly brackets.
# Another difference is that by calling a function, control is transferred to
# the functions. Macros are executed as if the body of the macros are not
# creating scopes regarding variables and control flow. Consequently, it is
# highly recommended to avoid calling return() in macros as this would stop
# the scope from executing where the macro is called.

# Generator expressions.
# Generator expressions are small statements that are evaluated during the
# configuration phase of the build. Most functions allow generator expressions
# to be used, with a few exceptions. They take the form of $<OPERATOR:VALUE>,
# where OPERATOR is applied or compared to VALUE. You can think of generator
# expressions as small inline if-statements.
target_compile_options(Chapter1 PRIVATE
        "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>")

message(STATUS "CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}.")
add_compile_options(-g)
message(STATUS "CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}.")
