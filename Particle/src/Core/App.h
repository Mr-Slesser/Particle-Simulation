#ifndef APP_H
#define APP_H

#include "Window/Window.h"
#include "../OpenGL/Renderer.h"
#include "GUI/GUILayer.h"

#include "Camera/CameraManager.h"
#include "Input/InputManager.h"

#include "../Particle/Emitter/EmitterManager.h"

// TODO: UUID for each system?

namespace PT
{
class App
{
private:
    Window *window;
    GL::Renderer *renderer;
    GUILayer *gui;

    EmitterManager *emitters;

public:
    App();
    ~App();

    bool init();
    void run();
};

} // namespace PT

#endif /* APP_H */
