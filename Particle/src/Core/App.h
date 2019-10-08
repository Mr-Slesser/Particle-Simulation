#ifndef APP_H
#define APP_H

#include "../Simulation/Container.h"
#include "../Utility/ConfigReader.h"
#include "../OpenGL/Programs/ProgramManager.h"
#include "../OpenGL/Renderers/DebugRenderer.h"
#include "../OpenGL/Renderers/MeshRenderer.h"
#include "../OpenGL/Buffers/TextureBuffer.h"
#include "GUI/GUILayer.h"
#include "../OpenGL/Primitives/Cube.h"
#include "Simulation/Terrain.h"

namespace PT
{
class App
{
private:
    Window window;

    double lastFrameTime = 0.0f;
    double dt;
    double fpsTarget = 600.0f;
  	double maxPeriod = 1.0 / fpsTarget;
  	bool debugDraw = true;

  	int maxParticles;

	std::shared_ptr<GL::ProgramManager> programs;
	std::shared_ptr<GL::DebugRenderer> debugRenderer;
	std::shared_ptr<GL::MeshRenderer> meshRenderer;
  	std::shared_ptr<GL::DebugData> debugDatastore;

  	std::unique_ptr<Container> container;
  	std::shared_ptr<Terrain> p;

  	GUILayer *gui;

public:
    App();
    ~App();

    bool init();
    void run();
};

} // namespace PT

#endif /* APP_H */
