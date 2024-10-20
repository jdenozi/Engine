#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Layout.h"

class ImGuiManagerClass {
public:
    ImGuiManagerClass(const ImGuiManagerClass &) = delete;

    ~ImGuiManagerClass() {
        shutdown();
    }

    static ImGuiManagerClass &getInstance() {
        static ImGuiManagerClass ref;
        return ref;
    }

    bool init(GLFWwindow *window) {
        if (initialized) { return true; }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable docking
        (void) io;

        ImGui::StyleColorsDark();

        if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
            throw std::runtime_error("Failed to initialize ImGui GLFW implementation");
        }
        if (!ImGui_ImplOpenGL3_Init("#version 130")) {
            throw std::runtime_error("Failed to initialize ImGui OpenGL3 implementation");
        }

        layoutManager = std::make_unique<LayoutManager>();
        initialized = true;
        return true;
    }

    void newFrame() const {
        if (!initialized) { throw std::runtime_error("ImGuiManager not initialized"); }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        layoutManager->createLayout();
    }

    void render() const {
        if (!initialized) { throw std::runtime_error("ImGuiManager not initialized"); }
        layoutManager->renderPanels();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void shutdown() {
        if (!initialized) { return; }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        initialized = false;
    }

    static void showDemoWindow() {
        ImGui::ShowDemoWindow();
    }

private:
    ImGuiManagerClass() = default;
    std::unique_ptr<LayoutManager> layoutManager;
    bool initialized = false;
};

static ImGuiManagerClass &ImGuiManager = ImGuiManagerClass::getInstance();