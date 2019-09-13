#ifndef GUILAYER_H
#define GUILAYER_H

// Include: ImGUI
#include "Headers/ImGUI.hpp"

#include "../Camera/CameraManager.h"
#include "../Window/Window.h"
#include "../../Simulation/ForceGrid.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace PT
{
class GUILayer
{
private:
    std::vector<std::function<void()>> windows;
    bool show_demo_window = false;
    ImGuiIO *io;
    //ImVec4 clear_color;
    GLFWwindow *window;

public:
    GUILayer();
    virtual ~GUILayer();

    void constantElements();
    void addElement(std::function<void()> window);
    bool init(GLFWwindow *_window);
    void render(bool *debug, ForceGrid *forcegrid0, ForceGrid *forcegrid1);

    void begin();
    void end();
};

} // namespace PT

#endif /* GUILAYER_H */
