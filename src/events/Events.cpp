#include <iostream>
#include "Events.h"
#include "engine/Engine.h"

Events::Events() {

}

void Events::polls() {

}


void Events::init() {
    auto w = EngineCore.window();
    glfwSetWindowCloseCallback(w.get(), [](GLFWwindow *w){
        EngineCore.exit();
    });
}
