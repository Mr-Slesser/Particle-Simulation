#include "PCHeader.h"
#include "App.h"

PT::App::App()
	: dt(0.0)
{
}

PT::App::~App()
{
  delete gui;
}

bool PT::App::init()
{
  PROFILE("App::init");

  Log::init();
  Utils::ApplicationData *d = Utils::ConfigReader::ReadConfig(PATH("config.ini"));
  if (d == nullptr)
  {
	GL_LOG_CRITICAL("GL::App::init() -> Failed to read configuration file");
	return false;
  }

  maxParticles = d->maxParticles;

  // Window
  if (!window.Init(WindowConfig(d->windowWidth, d->windowHeight, d->wireframe, d->fullscreen)))
  {
	CORE_LOG_TRACE("EXIT: Window initialization failed");
	return false;
  }

  window.AttachCamera(Camera());

  // Datastores
  debugDatastore = std::make_unique<GL::DebugData>();
  container = std::make_unique<Container>(0.0f, 0.0f, 0.0f, 600.0f, 200.0f, 500.0f);
  container->SubmitDebugOutline(debugDatastore);
  debugDatastore->Init();

  p = std::make_shared<Terrain>(0.0f, 0.0f, 0.0f, 1200.0f, 600.0f, 900.f, 5);
  p->Generate();

  // Programs
  programs = std::make_unique<GL::ProgramManager>();
  if (!programs->Init())
  {
	GL_LOG_CRITICAL("GL::Renderer::init() -> Program Manager failed to init");
	return false;
  }

  // Renderers
  debugRenderer = std::make_unique<GL::DebugRenderer>();
  if (!debugRenderer->Init(programs, debugDatastore))
  {
	CORE_LOG_TRACE("EXIT: Debug Renderer initialization failed");
	return false;
  }

  meshRenderer = std::make_unique<GL::MeshRenderer>();
  if (!meshRenderer->Init(programs))
  {
	CORE_LOG_TRACE("EXIT: Mesh Renderer initialization failed");
	return false;
  }

  // GUI
  gui = new GUILayer();
  if (!gui->init(window.Context()))
  {
	CORE_LOG_TRACE("EXIT: GUI Layer initialization failed");
	return false;
  }

  return true;
}

void PT::App::run()
{
  while (window.IsActive())
  {
	PROFILE("App::run");

	{
	  // Timing Functions
	  double time = glfwGetTime();
	  dt = (time - lastFrameTime);
	  lastFrameTime = time;
	}

	glfwPollEvents();
	processInput(&window);

	{
	  // Begin Draw
	  window.Clear();
	  meshRenderer->Draw(p);
	  debugRenderer->Draw();

//	  gui->begin();
//	  gui->constantElements();
//	  gui->render(simulation);
//	  gui->end();

	  window.SwapBuffers();
	  // End Draw
	}
  }
}