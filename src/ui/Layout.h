#include "imgui.h"
#include "imgui_internal.h"
#include "ecs/base/Cube.h"


class LayoutManager {
private:
    Cube cube;
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

        ImGui::Text("Camera Position");
        ImGui::SliderFloat("Camera X", &cube.position.x, -100.0f, 100.0f);
        ImGui::SliderFloat("Camera Y", &cube.position.y, -100.0f, 100.0f);
        ImGui::SliderFloat("Camera Z", &cube.position.z, -100.0f, 100.0f);

        // Add Rotation controls
        ImGui::Separator();
        // Store old values
        float oldX = cube.rotation.x;
        float oldY = cube.rotation.y;
        float oldZ = cube.rotation.z;

        // Rotation controls
        ImGui::Text("Cube Rotation Axis");
        ImGui::SliderFloat("Rotation X", &cube.rotation.x, -1.0f, 1.0f);
        ImGui::SliderFloat("Rotation Y", &cube.rotation.y, -1.0f, 1.0f);
        ImGui::SliderFloat("Rotation Z", &cube.rotation.z, -1.0f, 1.0f);

        // If any value changed, apply the rotation
        if (oldX != cube.rotation.x || oldY != cube.rotation.y || oldZ != cube.rotation.z) {
            cube.applyRotation();
        }

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
        // Get the size of the ImGui window content region
        ImVec2 windowSize = ImGui::GetContentRegionAvail();


        // Create a texture to render the OpenGL scene
        GLuint textureColorbuffer;
        glGenTextures(1, &textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.x, windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Create a framebuffer object
        GLuint framebuffer;
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

        // Render the cube
        cube.render(windowSize.x, windowSize.y);

        // Unbind the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Display the rendered texture in the ImGui window
        ImGui::Image(ImTextureID((void*)(intptr_t)textureColorbuffer), windowSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
    }
};
