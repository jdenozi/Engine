include(FetchContent)

# Add GLFW
FetchContent_Declare(
        GLFW
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8
)

FetchContent_GetProperties(GLFW)
if(NOT glfw_POPULATED)
    FetchContent_Populate(GLFW)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target" FORCE)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# Add GLEW
FetchContent_Declare(
        GLEW
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
        GIT_TAG        master
)

FetchContent_GetProperties(GLEW)
if(NOT GLEW_POPULATED)
    FetchContent_Populate(GLEW)

    # Adjust GLEW options as needed
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the GLEW shared library" FORCE)
    set(ONLY_LIBS ON CACHE BOOL "Build only the GLEW library" FORCE)
    add_subdirectory(${glew_SOURCE_DIR}/build/cmake ${glew_BINARY_DIR})
    include_directories(${glew_SOURCE_DIR}/include)

endif()

FetchContent_Declare(
        GLM
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        master
)

FetchContent_GetProperties(GLM)
if(NOT GLM_POPULATED)
    FetchContent_Populate(GLM)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG master
        EXCLUDE_FROM_ALL
)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)

    file(GLOB IMGUI_SOURCES
            "${imgui_SOURCE_DIR}/*.cpp"
            "${imgui_SOURCE_DIR}/*.h"
    )


    add_library(imgui STATIC ${IMGUI_SOURCES})
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

    target_sources(imgui PRIVATE
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    )
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR}/backends)
endif()


