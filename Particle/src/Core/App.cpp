#include "App.h"

PT::App::App()
    : dt(0.0f)
{
    init();
}

PT::App::~App()
{
    glfwTerminate();
}

void PT::App::init()
{
    window = new Window();
    window->init();

    //renderer = new GL::GLRenderer();
    renderer = new PTRenderer();
    renderer->init();
    InputManager::get()->registerMouseCallbacks(window);
}

void PT::App::run()
{
    while (window->isActive())
	{
        dt += 0.01;
		
        renderer->clear();
        processInput();
        renderer->draw(dt, CameraManager::get()->getCamera());

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

    float cSpeed = 0.05f;
    if (glfwGetKey(window->context(), GLFW_KEY_W) == GLFW_PRESS)
        CameraManager::get()->getCamera()->addPosition(cSpeed * CameraManager::get()->getCamera()->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_S) == GLFW_PRESS)
        CameraManager::get()->getCamera()->subtractPosition(cSpeed * CameraManager::get()->getCamera()->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_A) == GLFW_PRESS)
        CameraManager::get()->getCamera()->subtractPosition(glm::normalize(glm::cross(CameraManager::get()->getCamera()->getFront(), CameraManager::get()->getCamera()->getUp())) * cSpeed);
    if (glfwGetKey(window->context(), GLFW_KEY_D) == GLFW_PRESS)
        CameraManager::get()->getCamera()->addPosition(glm::normalize(glm::cross(CameraManager::get()->getCamera()->getFront(), CameraManager::get()->getCamera()->getUp())) * cSpeed);
}