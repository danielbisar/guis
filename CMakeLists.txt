cmake_minimum_required(VERSION 3.18.4)

# needs to be called before other methods, otherwise
# strange errors might happen
project(clang-test)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# necessary at least on ubuntu
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/")

link_directories("/usr/lib/x86_64-linux-gnu/")

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL 3.2 REQUIRED)

add_executable(clang-test clang-test.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "$HOME/src/skia/libskia-dev/skia/include/core" ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} dl glfw "/home/daniel/src/skia/libskia-dev/skia/out/Static/libskia.a" ${OPENGL_LIBRARIES})
