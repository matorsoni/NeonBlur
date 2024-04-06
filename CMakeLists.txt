cmake_minimum_required(VERSION 3.10)

project(NeonBlur)

add_subdirectory(deps/glfw-3.4)

add_executable(
    NeonBlur
        deps/glad/src/gl.c
        src/main.cpp
)

target_include_directories(
    NeonBlur
    PRIVATE
        deps/glad/include
        deps/glfw-3.4/include
)

target_link_libraries(
    NeonBlur
        glfw
)
