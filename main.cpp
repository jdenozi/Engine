#include <iostream>
#include "engine/Engine.h"
#include "timer/Timer.h"
#include "events/Events.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ui/ImGuiManager.h"

int main() {
    EngineCore.init();
    PoolEvent.init();
    BaseTimer.init();
    ImGuiManager.init(EngineCore.window().get());

    static char buf[256] = "";
        float f = 0.0f;

    while(EngineCore.isRunning()){
        EngineCore.update();
        PoolEvent.polls();
        BaseTimer.tick();

        ImGuiManager.newFrame();
        ImGui::Begin("ImGui Window");
        ImGui::Text("Hello, world %d", 123);
        if (ImGui::Button("Save"))
            //MySaveFunction();
        ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::End();

        glClear(GL_COLOR_BUFFER_BIT);
        ImGuiManager.render();
        glfwSwapBuffers(EngineCore.window().get());
        glfwPollEvents();
    }


    return EXIT_SUCCESS;
}