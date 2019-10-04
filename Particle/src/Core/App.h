#ifndef APP_H
#define APP_H

#include "../Utility/ConfigReader.h"
#include "Window/Window.h"
#include "../OpenGL/Programs/ProgramManager.h"
#include "../OpenGL/Renderers/Renderer.h"
#include "../OpenGL/Renderers/DebugRenderer.h"
#include "../OpenGL/Renderers/MeshRenderer.h"
#include "../OpenGL/Datastores/DebugDatastore.h"
#include "../OpenGL/Datastores/Datastore.h"
#include "../Simulation/Simulation.h"
#include "../Simulation/ForceGrid.h"
#include "GUI/GUILayer.h"
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
    double fpsTarget = 600.0f;
  	double maxPeriod = 1.0 / fpsTarget;
  	bool debugDraw = true;

    GL::ProgramManager *programs;
    GL::Renderer *renderer;
    GL::DebugRenderer *debugRenderer;
    GL::MeshRenderer *meshRenderer;
    GL::Datastore *datastore;
    GL::DebugDatastore *debugDatastore;
  	GL::MeshDatastore *meshDatastore;

  	GUILayer *gui;
    Simulation *simulation;
    EmitterManager *emitters;

public:
    App();
    ~App();

    bool init();
    void run();
};

} // namespace PT

#endif /* APP_H */
