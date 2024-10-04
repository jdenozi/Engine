
#include "Engine.h"
#include "memory"

Engine::Engine():m_running(false), m_height(WINDOW_HEIGHT), m_width(WINDOW_WIDTH) {
    const char* project_name = {};
    #if defined (PROJECT_NAME)
        project_name = PROJECT_NAME;
    #endif

    glfwInit();
    m_window = std::shared_ptr<GLFWwindow>(
            glfwCreateWindow(m_width, m_height, PROJECT_NAME, nullptr, nullptr),
            [](GLFWwindow* w) { glfwDestroyWindow(w); }
    );

    glfwMakeContextCurrent(m_window.get());
    glewInit();
}

void Engine::init() {
    m_running = true;
}

Engine::~Engine() {

}

void Engine::exit() {
    glfwWindowShouldClose(m_window.get());
    m_running = false;
}

void Engine::update() {
    glfwPollEvents();
}
