#include "PCHeader.h"
#include "App.h"

PT::App::App()
    : dt(0.0), paused(false)
{
}

PT::App::~App()
{
    delete emitters;
    delete simulation;
    delete programs;
    delete renderer;

    glfwTerminate();
}

bool PT::App::init()
{
    PROFILE("App::init");

    Log::init();
    CORE_LOG_TRACE("Logger startup: [Core]");
    GL_LOG_TRACE("  Logger startup: [GL  ]");

    // Window
    window = new Window();
    if (window->init() == nullptr)
    {
        CORE_LOG_TRACE("EXIT: Window initialization failed");
        return false;
    }

    // Datastores
    datastore = new GL::Datastore();
    debugDatastore = new GL::DebugDatastore();

    // Programs
    programs = new GL::ProgramManager();
    if (!programs->init())
    {
        GL_LOG_CRITICAL("GL::Renderer::init() -> Program Manager failed to init");
        return false;
    }

    // Renderers & Forces
    simulation = new Simulation(50, 2, 50, 5, datastore, debugDatastore);

    renderer = new GL::Renderer();
    debugRenderer = new GL::DebugRenderer();

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

    // InputManager
    InputManager::get()->registerMouseCallbacks(window);

    // GUI
    gui = new GUILayer();
    if (!gui->init(window->context()))
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
    while (window->isActive())
    {
        PROFILE("App::run");
        double time = glfwGetTime();
        dt = (time - lastFrameTime);
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

		  renderer->clear();
		  renderer->draw(dt);

		  if (this->debugDraw)
			  debugRenderer->draw(debugDatastore);

		  gui->begin();
		  gui->constantElements();
		  gui->render(simulation);
		  gui->end();
		  glfwSwapBuffers(window->context());
    }
}