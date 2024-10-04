cmake_minimum_required(VERSION 3.28)
project(
        GameEngine
        VERSION 0.0.1
        DESCRIPTION "OpenGL + EGUI Game Engine (not very original I know)"
        LANGUAGES CXX
)

include(Dependencies.cmake)
include_directories(libs/glfw)
include_directories(src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp
        src/engine/Engine.h
        src/engine/Engine.cpp
        src/timer/Timer.h
        src/timer/Timer.cpp
)


target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h
)

target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glew glm)
target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS})

# Create CPP variable
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME="${PROJECT_NAME} v${PROJECT_VERSION}")