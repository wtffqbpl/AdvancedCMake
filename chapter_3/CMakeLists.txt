# Top-level CMakeLists file for the chapter 3 example content.
cmake_minimum_required(VERSION 3.21)

project(
        chapter_3
        VERSION 1.0
        DESCRIPTION "A collection of sample C++ applications and libraries to demonstrate creating libraries and executables"
        LANGUAGES CXX
)

# Add subdirectories with examples.
add_subdirectory(hello_world_standalone)
add_subdirectory(hello_shared_lib)
add_subdirectory(hello_static_lib)
add_subdirectory(hello_header_only)
add_subdirectory(hello_object_lib)
add_subdirectory(hello_world_lib)

# add an example executable
add_executable(chapter3)

# add sources to the example executable
target_sources(chapter3 PRIVATE src/main.cc)
# link libraries
target_link_libraries(
        chapter3
        PRIVATE ch3_hello_shared ch3_hello_static hello_header_only hello hello_obj_lib)

# The target of target_link_libraries can also be another library. Again, the libraries are linked
# using an access specifier, which is either of the following:
#   PRIVATE: The library is used to link against, but it is not a part of the public interface.
#            The linked library is only a requirement when you're building the target.
#   INTERFACE: The library is not linked against, but it is part of the public interface. The linked
#            library is a requirement when you're using the target somewhere else. This is usually
#            only used when you're linking header-only libraries from other header-only libraries.
#   PUBLIC: The library is linked against, and it is part of the public interface. So, the library
#            library is both a build dependency and a usage dependency.

# target_compile_options(
#         chapter3
#         PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/SomeOption>
#                 $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-someOption>
# )
# By enabling the CMAKE_EXPORT_COMPILE_COMMANDS variables, a file called compile_commands.json
# containing the full commands for compiling is created in the build folder.