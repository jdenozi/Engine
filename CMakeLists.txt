cmake_minimum_required(VERSION 3.28)
project(
        GameEngine
        VERSION 0.0.1
        DESCRIPTION "OpenGL + EGUI Game Engine (not very original I know)"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

include(Dependencies.cmake)
include_directories(libs/GLFW)
include_directories(src)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/logs)

add_executable(${PROJECT_NAME} main.cpp
        src/engine/Engine.h
        src/engine/Engine.cpp
        src/timer/Timer.h
        src/timer/Timer.cpp
        src/events/Events.h
        src/events/Events.cpp
        src/events/Events.cpp
        src/utility/Logger.h
        src/utility/Logger.cpp
        src/ecs/ECS.h
        src/ecs/base/Types.h
        src/ecs/base/Component.h
        src/ecs/base/System.h
        src/ecs/base/System.h
        src/ecs/base/ComponentArray.h
        src/ecs/base/EntityManager.h
        src/ui/ImGuiManager.h
        src/ui/Layout.h
        src/ui/Style.h
)

target_compile_options(${PROJECT_NAME} PRIVATE -isystem /usr/lib/llvm-project/include/c++/v1/ -std=c++20 )

target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h
)

target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glew glm fmt::fmt-header-only imgui)
target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS})

# Create CPP variable
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME="${PROJECT_NAME} v${PROJECT_VERSION}")