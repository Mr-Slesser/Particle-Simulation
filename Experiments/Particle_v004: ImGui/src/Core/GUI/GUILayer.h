#ifndef GUILAYER_H
#define GUILAYER_H

#include "../../OpenGL/OpenGL.h"

#include "../../Headers/imgui/imgui.h"
#include "../../Headers/imgui/imgui_impl_glfw.h"
#include "../../Headers/imgui/imgui_impl_opengl3.h"

#include "../GlobalConfiguration.h"

#include "../Camera/CameraManager.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace PT
{
    class GUILayer
    {
    private:
        ImGuiIO io;
        bool show_demo_window = false;
        ImVec4 clear_color;

    public:
        GUILayer();
        virtual ~GUILayer();

        bool init(GLFWwindow* window);
        void render();
    };
    
} // namespace PT


#endif /* GUILAYER_H */
