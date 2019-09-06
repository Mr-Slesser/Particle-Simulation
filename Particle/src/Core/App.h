#ifndef APP_H
#define APP_H

#include "Window/Window.h"

#include "../OpenGL/Programs/ProgramManager.h"
#include "../OpenGL/Renderers/Renderer.h"
#include "../OpenGL/Renderers/DebugRenderer.h"
#include "../OpenGL/Datastores/DebugDatastore.h"
#include "../OpenGL/Datastores/Datastore.h"

#include "../Simulation/ForceGrid.h"
#include "GUI/GUILayer.h"

#include "Camera/CameraManager.h"
#include "Input/InputManager.h"

#include "../Utility/Timer.h"

#include "../Particle/Emitter/EmitterManager.h"

namespace PT
{
class App
{
private:
    Window *window;

    GL::ProgramManager *programs;
    GL::Renderer *renderer;
    GL::DebugRenderer *debugRenderer;
    GL::Datastore *datastore;
    GL::DebugDatastore *debugDatastore;

    GUILayer *gui;

    ForceGrid *forces;

    EmitterManager *emitters;

public:
    App();
    ~App();

    bool init();
    void run();
};

} // namespace PT

#endif /* APP_H */
