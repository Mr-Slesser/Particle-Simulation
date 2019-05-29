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
    GL_LOG_TRACE("Logger startup: [Core]");
    GL_LOG_TRACE("Logger startup: [GL  ]");    

    // Window
    window = new Window();
    if (window->init() == nullptr)
    {
        CORE_LOG_TRACE("EXIT: Window initialization failed");
        return false;
    }

    // Renderer
    renderer = new GL::Renderer();
    if (!renderer->init())
    {
        CORE_LOG_TRACE("EXIT: Renderer initialization failed");
        return false;
    }

    // InputManager
    //InputManager::get()->registerMouseCallbacks(window);

    // GUI
    gui = new GUILayer();
    if(!gui->init(window->context()))
    {
        CORE_LOG_TRACE("EXIT: GUI Layer initialization failed");
        return false;
    }

    return true;
}

void PT::App::run()
{
    while (window->isActive())
	{
		glfwPollEvents();
        processInput();

        renderer->clear();
        renderer->draw();
        
        gui->render();
		
        glfwSwapBuffers(window->context());
	}
}

// TODO: Add this into InputManager?
// TODO: Make sure no repeat keys unless specified?
void PT::App::processInput()
{
	if (glfwGetKey(window->context(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
		glfwSetWindowShouldClose(window->context(), true);
    }

    float cSpeed = 10.0f;
    if (glfwGetKey(window->context(), GLFW_KEY_W) == GLFW_PRESS)
        CameraManager::get()->getCamera()->addPosition(cSpeed * CameraManager::get()->getCamera()->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_S) == GLFW_PRESS)
        CameraManager::get()->getCamera()->subtractPosition(cSpeed * CameraManager::get()->getCamera()->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_A) == GLFW_PRESS)
        CameraManager::get()->getCamera()->subtractPosition(glm::normalize(glm::cross(CameraManager::get()->getCamera()->getFront(), CameraManager::get()->getCamera()->getUp())) * cSpeed);
    if (glfwGetKey(window->context(), GLFW_KEY_D) == GLFW_PRESS)
        CameraManager::get()->getCamera()->addPosition(glm::normalize(glm::cross(CameraManager::get()->getCamera()->getFront(), CameraManager::get()->getCamera()->getUp())) * cSpeed);

    if (glfwGetKey(window->context(), GLFW_KEY_Q) == GLFW_PRESS)
        renderer->addParticle(1000);
}