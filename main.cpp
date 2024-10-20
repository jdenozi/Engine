#include <iostream>
#include "engine/Engine.h"
#include "timer/Timer.h"
#include "events/Events.h"
#include "imgui.h"
#include "ui/ImGuiManager.h"
#include "ui/Style.h"

int main() {
    EngineCore.init();
    PoolEvent.init();
    BaseTimer.init();
    ImGuiManager.init(EngineCore.window().get());

    CustomStyle::ApplyStyle();
    while(EngineCore.isRunning()){
        EngineCore.update();
        PoolEvent.polls();
        BaseTimer.tick();
        ImGuiManager.newFrame();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGuiManager.render();
        glfwSwapBuffers(EngineCore.window().get());
        glfwPollEvents();
    }


    return EXIT_SUCCESS;
}