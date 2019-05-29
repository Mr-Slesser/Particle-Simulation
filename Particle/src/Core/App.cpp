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
    if(!gui->init(window->context()))
    {
        CORE_LOG_TRACE("EXIT: GUI Layer initialization failed");
        return false;
    }

    // TODO: Robust!
    CameraManager::get()->getCamera();
    CameraManager::get()->register_input_dispatch();

    return true;
}

void PT::App::run()
{
    while (window->isActive())
	{
		glfwPollEvents();
        InputManager::get()->processInput(window, renderer);

        renderer->clear();
        renderer->draw();
        
        gui->render();
		
        glfwSwapBuffers(window->context());
	}
}