#include <iostream>
#include "engine/Engine.h"
#include "timer/Timer.h"
#include "events/Events.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

int main() {
    EngineCore.init();
    PoolEvent.init();
    BaseTimer.init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(EngineCore.window().get(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    static char buf[256] = "";
        float f = 0.0f;

    while(EngineCore.isRunning()){
        EngineCore.update();
        PoolEvent.polls();
        BaseTimer.tick();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("ImGui Window");
        ImGui::Text("Hello, world %d", 123);
        if (ImGui::Button("Save"))
            //MySaveFunction();
        ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::End();

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(EngineCore.window().get());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return EXIT_SUCCESS;
}