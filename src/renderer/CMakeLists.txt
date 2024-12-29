set(RENDERER_SOURCES
    renderer.cpp
)

set(RENDERER_HEADERS
    renderer.h
)

add_library(renderer STATIC
    ${RENDERER_SOURCES}
    ${RENDERER_HEADERS}
    camera.h
    camera.cpp
    rendererobject.h
    cube.h
)

target_include_directories(renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries(renderer PRIVATE
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets
    )
else()
    target_link_libraries(renderer PRIVATE
        Qt::Widgets
        Qt::OpenGL
    )
endif()
