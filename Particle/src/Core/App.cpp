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
    GL_LOG_TRACE("Core Logger Started");
    GL_LOG_TRACE("GL Logger Started");    

    // Window
    window = new Window();
    if (window->init() == nullptr)
    {
        CORE_LOG_TRACE("Exiting: Window initialization failed");
        return false;
    }

    // Renderer
    renderer = new GL::Renderer();
    if (!renderer->init())
    {
        CORE_LOG_TRACE("Exiting: Renderer initialization failed");
        return false;
    }

    // InputManager
    InputManager::get()->registerMouseCallbacks(window);

    return true;
}

void PT::App::run()
{
    while (window->isActive())
	{
        processInput();
        renderer->clear();
        renderer->update();
        renderer->draw();

		glfwSwapBuffers(window->context());
		glfwPollEvents();
	}
}

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
}