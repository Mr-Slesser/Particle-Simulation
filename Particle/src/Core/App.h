#ifndef APP_H
#define APP_H

#include "Window/Window.h"

#include "../OpenGL/Programs/ProgramManager.h"
#include "../OpenGL/Renderers/Renderer.h"
#include "../OpenGL/Renderers/DebugRenderer.h"
#include "../OpenGL/Datastores/DebugDatastore.h"
#include "../OpenGL/Datastores/Datastore.h"

#include "../Simulation/Simulation.h"
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
    double lastFrameTime = 0.0f;
    double dt;

    bool debugDraw = true;

    GL::ProgramManager *programs;
    GL::Renderer *renderer;
    GL::DebugRenderer *debugRenderer;
    GL::Datastore *datastore;
    GL::DebugDatastore *debugDatastore;

    GUILayer *gui;

    Simulation *simulation;
    // Utils::Perlin *perlin0;
    // Utils::Perlin *perlin1;

    // ForceGrid *forces0;
    // ForceGrid *forces1;

    EmitterManager *emitters;

public:
    App();
    ~App();

    bool init();
    void run();

    inline bool shouldDrawDebug() const { return debugDraw; }
    void setDrawDebug(bool to) { debugDraw = to; }
};

} // namespace PT

#endif /* APP_H */
