#include "App.h"

App::App()
    : dt(0.0f)
{
    init();
}

App::~App()
{
    glfwTerminate();
}

void App::init()
{
    window = new Window();
    window->init();

    v[0] = {{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}};
    v[1] = {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}};
    v[2] = {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
    v[3] = {{-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}};

    renderer = new GL::GLRenderer();
    renderer->init(indices, v, sizeof(v));

    //cam = new Camera2D();
    cam = new Camera3D();

    PT::Input::InputManager::get()->registerMouseCallbacks(window);
}

void App::run()
{
    while (window->isActive())
	{
        dt += 0.01;
		
        renderer->clear();
        processInput();
        renderer->draw(dt, cam);

		glfwSwapBuffers(window->context());
		glfwPollEvents();
	}
}

void App::processInput()
{
	if (glfwGetKey(window->context(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
		glfwSetWindowShouldClose(window->context(), true);
    }

    float cSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window->context(), GLFW_KEY_W) == GLFW_PRESS)
        cam->addPosition(cSpeed * cam->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_S) == GLFW_PRESS)
        cam->subtractPosition(cSpeed * cam->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_A) == GLFW_PRESS)
        cam->subtractPosition(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cSpeed);
    if (glfwGetKey(window->context(), GLFW_KEY_D) == GLFW_PRESS)
        cam->addPosition(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cSpeed);
}