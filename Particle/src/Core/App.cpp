#include "PCHeader.h"
#include "App.h"

PT::App::App()
{
}

PT::App::~App()
{
    glfwTerminate();
}

bool PT::App::init()
{
    Log::init();
    CORE_LOG_TRACE("Logger startup: [Core]");
    GL_LOG_TRACE("  Logger startup: [GL  ]");

    // SECTION: Window
    window = new Window();
    if (window->init() == nullptr)
    {
        CORE_LOG_TRACE("EXIT: Window initialization failed");
        return false;
    }

    // SECTION: Renderer
    renderer = new GL::Renderer();
    if (!renderer->init())
    {
        CORE_LOG_TRACE("EXIT: Renderer initialization failed");
        return false;
    }

    // SECTION: InputManager
    InputManager::get()->registerMouseCallbacks(window);

    // SECTION: GUI
    gui = new GUILayer();
    if (!gui->init(window->context()))
    {
        CORE_LOG_TRACE("EXIT: GUI Layer initialization failed");
        return false;
    }

    // TODO: Robust!
    CameraManager::get()->getCamera();
    CameraManager::get()->register_input_dispatch();

    emitters = new EmitterManager();
    emitters->addEmitter(gui, S_TO_MS(0.1), Colour::GREEN);
    emitters->addEmitter(gui, S_TO_MS(0.4), Colour::BLUE);

    return true;
}

void PT::App::run()
{
    while (window->isActive())
    {
        glfwPollEvents();
        InputManager::get()->processInput(window, renderer);

        renderer->clear();

        emitters->update();
        emitters->submit(renderer);

        renderer->draw();

        gui->begin();
        gui->constantElements();
        gui->render();
        gui->end(window);

        glfwSwapBuffers(window->context());
    }
}