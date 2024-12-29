# src/ui/CMakeLists.txt
set(UI_SOURCES
    mainwindow.cpp
)

set(UI_HEADERS
    mainwindow.h
)

add_library(ui STATIC
    ${UI_SOURCES}
    ${UI_HEADERS}
)

target_include_directories(ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../renderer
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries(ui PRIVATE
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets
        renderer
    )
else()
    target_link_libraries(ui PRIVATE
        Qt::Widgets
        Qt::OpenGL
        renderer
    )
endif()
