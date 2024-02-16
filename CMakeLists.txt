cmake_minimum_required(VERSION 3.22.1)

set(PROJECT_TRIANGLE "boids2D")

project(${PROJECT_TRIANGLE} VERSION 0.1.0)

#cmake_policy(SET CMP0072 NEW)
#set(CMAKE_CXX_STANDARD 11.4.0)

find_package(OpenGL REQUIRED)
find_path(STB_INCLUDE_DIRS "stb.h")

# Add ImGui source files
set(IMGUI_DIR "./include/imgui")
set(IMGUI_DIR_BACK "./include/imgui/backends")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(SRC ./src)
set(INCLUDE ./include)
# set(SHADERS ./shaders)

set(SRC_FILES
    ${SRC}/main.cpp
    ${SRC}/kore/glad.c
    ${SRC}/kore/shape.cpp
    ${SRC}/main_scene.cpp
    ${IMGUI_SOURCES}
)

set(LINK_LIB
    glfw
    OpenGL::GL
)

# include_directories(${SHADERS})
include_directories(${INCLUDE})
add_executable(${PROJECT_TRIANGLE} ${SRC_FILES})
target_link_libraries(${PROJECT_TRIANGLE} ${LINK_LIB})
target_include_directories(${PROJECT_TRIANGLE} PRIVATE ${IMGUI_DIR} ${IMGUI_DIR_BACK})