cmake_minimum_required(VERSION 3.18.4)

# needs to be called before other methods, otherwise
# strange errors might happen
project(guis)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# necessary at least on ubuntu
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_C_STANDARD 17)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSK_GL" )

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

link_directories("/usr/lib/x86_64-linux-gnu/")

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "src/"
    "../skia/skia/include"
    "../skia/skia"
    "submodules/simpleREPL/src"
    ${OPENGL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    dl
    glfw
    "${CMAKE_SOURCE_DIR}/../skia/skia/out/static/libskia.a"
    jpeg
    freetype
    z
    png
    fontconfig
    webp
    webpmux
    webpdemux
    pthread
    yaml-cpp
    ${OPENGL_LIBRARIES})
