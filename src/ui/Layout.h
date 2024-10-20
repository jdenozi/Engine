#include "ImGuiManager.h"
#include "imgui.h"
#include "imgui_internal.h"

class LayoutManager {
public:
    void createLayout() {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        static bool first_time = true;
        if (first_time) {
            first_time = false;

            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

            auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
            auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.2f, nullptr, &dockspace_id);
            auto dock_id_bottom = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.2f, nullptr, &dockspace_id);

            ImGui::DockBuilderDockWindow("Left Column", dock_id_left);
            ImGui::DockBuilderDockWindow("Right Column", dock_id_right);
            ImGui::DockBuilderDockWindow("Bottom Panel", dock_id_bottom);
            ImGui::DockBuilderDockWindow("Center View", dockspace_id);

            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGui::End();
    }

    void renderPanels() {
        // Left Column
        ImGui::Begin("Left Column");

        // Camera position
        static float cameraPos[3] = {0.0f, 0.0f, 0.0f};
        ImGui::Text("Camera Position");
        ImGui::SliderFloat("X", &cameraPos[0], -10.0f, 10.0f);
        ImGui::SliderFloat("Y", &cameraPos[1], -10.0f, 10.0f);
        ImGui::SliderFloat("Z", &cameraPos[2], -10.0f, 10.0f);

        // Number of objects
        static int numObjects = 0;
        ImGui::InputInt("Number of Objects", &numObjects);

        // FPS display
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        // Other information
        ImGui::Text("Other Information");
        ImGui::BulletText("Screen Resolution: %dx%d", (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        ImGui::BulletText("Time: %.2f", ImGui::GetTime());

        ImGui::End();

        // Right Column
        ImGui::Begin("Right Column");
        ImGui::Text("This is the right column");
        ImGui::End();

        // Bottom Panel
        ImGui::Begin("Bottom Panel");
        ImGui::Text("This is the bottom panel");
        ImGui::End();

        // Center View
        ImGui::Begin("Center View");
        ImGui::Text("This is where your scene will be rendered");
        // RENDER SCENE HERE
        ImGui::End();
    }
};