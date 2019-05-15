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

    v[0] = {{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}};
    v[1] = {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}};
    v[2] = {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
    v[3] = {{-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}};

    renderer = new GL::GLRenderer();
    renderer->init(indices, v, sizeof(v));
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