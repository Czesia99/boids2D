cmake_minimum_required(VERSION 3.22.1)

set(PROJECT_TRIANGLE "boids2D")

project(${PROJECT_TRIANGLE} VERSION 0.1.0)

#cmake_policy(SET CMP0072 NEW)
#set(CMAKE_CXX_STANDARD 11.4.0)

find_package(OpenGL REQUIRED)

set(SRC ./src)
set(INCLUDE ./include)
# set(SHADERS ./shaders)

set(SRC_FILES
    ${SRC}/main.cpp
    ${SRC}/kore/glad.c
    ${SRC}/kore/shape.cpp
    ${SRC}/main_scene.cpp
)

set(LINK_LIB
    glfw
    OpenGL::GL
)

# include_directories(${SHADERS})
include_directories(${INCLUDE})
add_executable(${PROJECT_TRIANGLE} ${SRC_FILES})
target_link_libraries(${PROJECT_TRIANGLE} ${LINK_LIB})