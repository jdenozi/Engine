
#include "Engine.h"
#include "memory"

Engine::Engine() {
    const char* project_name = {};
    #if defined (PROJECT_NAME)
        project_name = PROJECT_NAME;
    #endif

    glfwInit();
    m_window = std::shared_ptr<GLFWwindow>(
            glfwCreateWindow(500, 500, PROJECT_NAME, nullptr, nullptr),
            [](GLFWwindow* w) { glfwDestroyWindow(w); }
    );

    glfwMakeContextCurrent(m_window.get());
    glewInit();

    while(!glfwWindowShouldClose(m_window.get())|| !isRunning()){
        glfwPollEvents();
    }
}

void Engine::init() {

}

Engine::~Engine() {

}

void Engine::exit() {
    m_running = false;
}

void Engine::update() {

}
