project(
        ch3_hello_header_only
        VERSION 1.0
        DESCRIPTION "Chapter 3 header-only example"
        LANGUAGES CXX)

add_library(hello_header_only INTERFACE)
target_include_directories(hello_header_only INTERFACE include/)
target_compile_features(hello_header_only INTERFACE cxx_std_17)