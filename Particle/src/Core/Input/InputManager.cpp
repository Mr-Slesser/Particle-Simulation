#include "PCHeader.h"
#include "InputManager.h"

namespace PT
{
InputManager *InputManager::instance = 0;

InputManager *InputManager::get()
{
    if (!instance)
        instance = new InputManager;
    return instance;
}

InputManager::InputManager()
    : mouseHeld(false), sensitivity(0.0f)
{
    sensitivity = 0.1f;
}

InputManager::~InputManager()
{
    delete instance;
    instance = nullptr;
}

void InputManager::registerMouseCallbacks(Window *window)
{
    glfwSetCursorPosCallback(window->Context(), PT::mouseCursorHandler);
    glfwSetMouseButtonCallback(window->Context(), PT::mouseButtonHandler);
    glfwSetScrollCallback(window->Context(), PT::mouseScrollHandler);
}

void InputManager::setMouseHeld(bool torf)
{
    mouseHeld = torf;
}

void InputManager::processInput(Window *window, GL::Renderer *renderer, PT::Simulation *simulation)
{
    if (glfwGetKey(window->Context(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window->Context(), true);
    }

    if (glfwGetKey(window->Context(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        simulation->AddParticle(particleFloodAmount);
    }

    dispatch(window);
}

bool InputManager::register_dispatch(const char *key_name, unsigned int key, CameraManager *dispatch_to)
{
    if (dispatchers.find(key) == dispatchers.end())
    {
        std::vector<CameraManager *> a;
        a.reserve(1);
        dispatchers[key] = a;
    }

    dispatchers[key].push_back(dispatch_to);
    CORE_LOG_INFO("InputManager -> Registered {}", key_name);
    return true;
}

void InputManager::dispatch(Window *window)
{
    for (auto const &d : dispatchers)
    {
        if (glfwGetKey(window->Context(), d.first) == GLFW_PRESS)
        {
            for (auto r : d.second)
            {
                r->receive_dispatched_input(d.first);
            }
        }
    }
}
} // namespace PT
