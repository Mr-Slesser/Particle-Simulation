#include "PCHeader.h"
#include "App.h"

PT::App::App()
	: dt(0.0)
{
}

PT::App::~App()
{
  delete simulation;
  delete programs;
  delete renderer;
  delete debugRenderer;
  delete meshRenderer;
  delete datastore;
  delete debugDatastore;
  delete meshDatastore;
  delete gui;
}

bool PT::App::init()
{
  PROFILE("App::init");

  Log::init();
  Utils::ApplicationData *d = Utils::ConfigReader::ReadConfig(PATH("config.ini"));
  if (d == nullptr)
  {
	GL_LOG_CRITICAL("GL::Renderer::init() -> Failed to read configuration file");
	return false;
  }

  GC::get()->init(d->maxParticles);

  // Window
  if (!window.Init(WindowConfig(d->windowWidth, d->windowHeight, d->wireframe, d->fullscreen)))
  {
	CORE_LOG_TRACE("EXIT: Window initialization failed");
	return false;
  }
  window.AttachCamera(Camera());

  // Datastores
  datastore = new GL::Datastore();
  debugDatastore = new GL::DebugDatastore();
  meshDatastore =
	  new GL::MeshDatastore(d->simWidth * d->simResolution, d->simDepth * d->simResolution, d->meshResolution);

  container = std::make_unique<Container>(0.0f, 0.0f, 0.0f, 600.0f, 200.0f, 500.0f);
  container->SubmitDebugOutline(debugDatastore);
  p = std::make_shared<Terrain>(0.0f, 0.0f, 0.0f, 600.0f, 200.0f, 500.f, 5);
  p->Generate();

  // Programs
  programs = new GL::ProgramManager();
  if (!programs->init())
  {
	GL_LOG_CRITICAL("GL::Renderer::init() -> Program Manager failed to init");
	return false;
  }

  // Renderers & Forces
  simulation = new Simulation(d->simWidth,
							  d->simHeight,
							  d->simDepth,
							  d->simResolution,
							  d->simYResolution,
							  datastore,
							  debugDatastore);
  textureBuffer = new TextureBuffer(GL_TEXTURE0, simulation->Force(0));

  renderer = new GL::Renderer();
  debugRenderer = new GL::DebugRenderer();
  meshRenderer = new GL::MeshRenderer();

  // Renderer
  if (!renderer->init(programs, datastore, simulation, textureBuffer))
  {
	CORE_LOG_TRACE("EXIT: Renderer initialization failed");
	return false;
  }

  // Debug Renderer
  if (!debugRenderer->init(programs, debugDatastore, simulation, textureBuffer))
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

	auto __simulation = simulation->__Update(dt);

	glfwPollEvents();
	processInput(&window);

	for (int i = 0; i < __simulation.size(); i++)
	{
	  __simulation[i].join();
	}

	textureBuffer->loadData();
	datastore->Update();
	meshDatastore->Update();

	{
	  // Begin Draw
	  window.Clear();
//	  window.SetWireframeMode(true);
	  meshRenderer->draw(p);
	  renderer->draw(dt);

	  debugRenderer->draw();

//	  gui->begin();
//	  gui->constantElements();
//	  gui->render(simulation);
//	  gui->end();

	  window.SwapBuffers();
	  // End Draw
	}
  }
}