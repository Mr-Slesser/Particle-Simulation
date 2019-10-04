#include "PCHeader.h"
#include "App.h"

PT::App::App()
	: dt(0.0)
{
}

PT::App::~App()
{
  delete emitters;
  delete simulation;
  delete programs;
  delete renderer;
  delete debugRenderer;
  delete meshRenderer;
  delete datastore;
  delete debugDatastore;
  delete meshDatastore;
  delete gui;

  glfwTerminate();
}

bool PT::App::init()
{
  PROFILE("App::init");

  Log::init();
  CORE_LOG_TRACE("Logger startup: [Core]");
  GL_LOG_TRACE("  Logger startup: [GL  ]");

  Utils::ApplicationData *d = Utils::ConfigReader::ReadConfig(PATH("config.ini"));
  if (d == nullptr)
  {
	GL_LOG_CRITICAL("GL::Renderer::init() -> Failed to read configuration file");
	return false;
  }

  GC::get()->init(d->maxParticles);
  InputManager::get()->setParticleFloodAmount(d->particleFloodNumber);

  // Window
  window = new Window(WindowConfig(d->windowWidth, d->windowHeight, d->wireframe, d->fullscreen));
  if (!window->Init())
  {
	CORE_LOG_TRACE("EXIT: Window initialization failed");
	return false;
  }
  Log_GL_Parameters();

  // Datastores
  datastore = new GL::Datastore();
  debugDatastore = new GL::DebugDatastore();
  meshDatastore = new GL::MeshDatastore(d->simWidth * d->simResolution, d->simDepth * d->simResolution, d->meshResolution);

  // Programs
  programs = new GL::ProgramManager();
  if (!programs->init())
  {
	GL_LOG_CRITICAL("GL::Renderer::init() -> Program Manager failed to init");
	return false;
  }

  // Renderers & Forces
  simulation = new Simulation(d->simWidth, d->simHeight, d->simDepth, d->simResolution, d->simYResolution, datastore, debugDatastore);

  renderer = new GL::Renderer();
  debugRenderer = new GL::DebugRenderer();
  meshRenderer = new GL::MeshRenderer();

  // Renderer
  if (!renderer->init(programs, datastore, simulation))
  {
	CORE_LOG_TRACE("EXIT: Renderer initialization failed");
	return false;
  }

  // Debug Renderer
  if (!debugRenderer->init(programs, simulation->Force(0), simulation->Force(1)))
  {
	CORE_LOG_TRACE("EXIT: Debug Renderer initialization failed");
	return false;
  }

  // Mesh Renderer
  if (!meshRenderer->init(programs, meshDatastore))
  {
	CORE_LOG_TRACE("EXIT: Mesh Renderer initialization failed");
	return false;
  }

  // InputManager
  InputManager::get()->registerMouseCallbacks(window);

  // GUI
  gui = new GUILayer();
  if (!gui->init(window->Context()))
  {
	CORE_LOG_TRACE("EXIT: GUI Layer initialization failed");
	return false;
  }

  CameraManager::get()->getCamera();
  CameraManager::get()->register_input_dispatch();

  // Emitters
  emitters = new EmitterManager();
  emitters->addEmitter(datastore, gui, S_TO_MS(0.1), Colour::GREEN);
  emitters->addEmitter(datastore, gui, S_TO_MS(0.4), Colour::BLUE);

  return true;
}

void PT::App::run()
{
  while (window->IsActive())
  {
	PROFILE("App::run");

	double time = glfwGetTime();
	dt = (time - lastFrameTime);

	if(dt >= maxPeriod)
	{
	  lastFrameTime = time;

	  auto __simulation = simulation->__Update(dt);

	  glfwPollEvents();
	  this->debugDatastore->beginDebug();

	  InputManager::get()->processInput(window, renderer, simulation);
	  emitters->update(debugDatastore);

	  for (int i = 0; i < __simulation.size(); i++)
	  {
		__simulation[i].join();
	  }

	  datastore->Update();
	  meshDatastore->Update();

	  renderer->clear();

	  //	meshRenderer->draw();
	  renderer->draw(dt);

	  if (this->debugDraw)
		debugRenderer->draw(debugDatastore);

	  gui->begin();
	  gui->constantElements();
	  gui->render(simulation);
	  gui->end();
	  glfwSwapBuffers(window->Context());
	}
  }
}