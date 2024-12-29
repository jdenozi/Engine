cmake_minimum_required(VERSION 3.16)
project(QtOpenGLEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
endif()

# Add subdirectories and set include directories
add_subdirectory(src/renderer)
add_subdirectory(src/ui)

# Set the target sources
set(PROJECT_SOURCES
    src/main.cpp
    resources.qrc
)

# Create executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtOpenGLEngine
        ${PROJECT_SOURCES}
    )
else()
    add_executable(QtOpenGLEngine
        ${PROJECT_SOURCES}
    )
endif()

# Include directories for the main executable
target_include_directories(QtOpenGLEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
)

# Link libraries
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries(QtOpenGLEngine PRIVATE
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets
        renderer
        ui
    )
else()
    target_link_libraries(QtOpenGLEngine PRIVATE
        Qt::Widgets
        Qt::OpenGL
        renderer
        ui
    )
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtOpenGLEngine)
endif()
