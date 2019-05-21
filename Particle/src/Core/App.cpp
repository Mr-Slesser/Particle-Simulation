#include "App.h"

PT::App::App()
{
    init();
}

PT::App::~App()
{
    glfwTerminate();
}

void PT::App::init()
{
    // Window
    window = new Window();
    window->init();

    // Renderer
    renderer = new GL::Renderer();
    renderer->init();
    // renderer->init(q.vertices, sizeof(Quad));

    // InputManager
    InputManager::get()->registerMouseCallbacks(window);
}

void PT::App::run()
{
    while (window->isActive())
	{
        processInput();
        renderer->clear();
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

    float cSpeed = 0.05f;
    if (glfwGetKey(window->context(), GLFW_KEY_W) == GLFW_PRESS)
        CameraManager::get()->getCamera()->addPosition(cSpeed * CameraManager::get()->getCamera()->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_S) == GLFW_PRESS)
        CameraManager::get()->getCamera()->subtractPosition(cSpeed * CameraManager::get()->getCamera()->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_A) == GLFW_PRESS)
        CameraManager::get()->getCamera()->subtractPosition(glm::normalize(glm::cross(CameraManager::get()->getCamera()->getFront(), CameraManager::get()->getCamera()->getUp())) * cSpeed);
    if (glfwGetKey(window->context(), GLFW_KEY_D) == GLFW_PRESS)
        CameraManager::get()->getCamera()->addPosition(glm::normalize(glm::cross(CameraManager::get()->getCamera()->getFront(), CameraManager::get()->getCamera()->getUp())) * cSpeed);

    if (glfwGetKey(window->context(), GLFW_KEY_Q) == GLFW_PRESS)
        renderer->changeShaders(1);
    if (glfwGetKey(window->context(), GLFW_KEY_E) == GLFW_PRESS)
        renderer->changeShaders(2);
}