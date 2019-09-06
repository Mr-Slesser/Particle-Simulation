#include "PCHeader.h"
#include "App.h"

PT::App::App()
{
}

PT::App::~App()
{
    delete emitters;
    delete forces;
    delete gui;
    delete programs;
    delete renderer;

    glfwTerminate();
}

bool PT::App::init()
{
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

    // Renderes & Forces
    forces = new PT::ForceGrid(100, 100, 5, 5, debugDatastore);
    renderer = new GL::Renderer();
    debugRenderer = new GL::DebugRenderer();

    // Renderer
    if (!renderer->init(programs, datastore, forces))
    {
        CORE_LOG_TRACE("EXIT: Renderer initialization failed");
        return false;
    }

    // Debug Renderer
    if (!debugRenderer->init(programs, forces))
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
        glfwPollEvents();
        InputManager::get()->processInput(window, renderer);

        renderer->clear();

        this->debugDatastore->beginDebug();

        forces->update();
        emitters->update(debugDatastore);
        datastore->Update();

        renderer->draw();

        debugRenderer->draw(debugDatastore);

        gui->begin();
        gui->constantElements();
        gui->render();
        gui->end(window);

        glfwSwapBuffers(window->context());
    }
}