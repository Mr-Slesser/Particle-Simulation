#ifndef GUILAYER_H
#define GUILAYER_H

#include "../Camera/CameraManager.h"
#include "../Window/Window.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace PT
{
class GUILayer
{
private:
    std::vector<std::function<void()>> windows;
    ImGuiIO io;
    bool show_demo_window = false;
    //ImVec4 clear_color;

public:
    GUILayer();
    virtual ~GUILayer();

    void constantElements();
    void addElement(std::function<void()> window);
    bool init(GLFWwindow *window);
    void render();

    void begin();
    void end(Window *window);
};

} // namespace PT

#endif /* GUILAYER_H */
