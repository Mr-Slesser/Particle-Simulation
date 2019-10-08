#ifndef GUILAYER_H
#define GUILAYER_H

// Include: ImGUI
#include "Headers/ImGUI.hpp"

#include "../Window/Window.h"
#include "../../Simulation/Simulation.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace PT
{
class GUILayer
{
private:
    std::vector<std::function<void()>> windows;
    ImGuiIO *io;
    GLFWwindow *window;

public:
    GUILayer();
    virtual ~GUILayer();

    void constantElements();
    void addElement(std::function<void()> window);
    bool init(GLFWwindow *_window);
    void render(Simulation *sim);

    void begin();
    void end();
};

} // namespace PT

#endif /* GUILAYER_H */
