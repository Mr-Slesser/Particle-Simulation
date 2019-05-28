#include "GUILayer.h"

namespace PT
{
    GUILayer::GUILayer()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        io = ImGui::GetIO();
        (void)io;
    }
    
    GUILayer::~GUILayer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GUILayer::init(GLFWwindow* window)
    {

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    }

    void GUILayer::render()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window) { ImGui::ShowDemoWindow(&show_demo_window); }

        {
            static glm::vec3 camera_pos;
            // static glm::vec3 camera_front;
            // static glm::vec3 camera_up;

            ImGui::Begin("Debug Variables");
            {
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                ImGui::Checkbox("Show Demo Window", &show_demo_window);

                ImGui::ColorEdit3("clear color", (float*)&clear_color);

                camera_pos = CameraManager::get()->getCamera()->getPosition();
                ImGui::SliderFloat3("Camera Pos", &camera_pos.x, -1000.0f, 1000.0f, "%.2f");
                CameraManager::get()->getCamera()->setPosition(camera_pos);

                // camera_front = CameraManager::get()->getCamera()->getFront();
                // ImGui::SliderFloat3("Camera Front", &camera_front.x, -10.0f, 10.0f, "%.2f");
                // CameraManager::get()->getCamera()->setFront(camera_front);

                // camera_up = CameraManager::get()->getCamera()->getUp();
                // ImGui::SliderFloat3("Camera Up", &camera_up.x, -10.0f, 10.0f, "%.2f");
                // CameraManager::get()->getCamera()->setUp(camera_up);
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} // namespace PT



