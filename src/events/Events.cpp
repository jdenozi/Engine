#include <iostream>
#include "Events.h"
#include "engine/Engine.h"
#include "utility/Logger.h"

Events::Events() {

}

void Events::polls() {

}

void Events::init() {
    auto w = EngineCore.window();
    glfwSetWindowCloseCallback(w.get(), [](GLFWwindow *w){
        LOG_DEBUG("Close application");
        EngineCore.exit();
    });
}
