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
        // TODO: Set this in config / init function
        sensitivity = 0.1f;
    }

    InputManager::~InputManager()
    {
        delete instance;
        instance = nullptr;

        // Clean up map!
    }

    void InputManager::registerMouseCallbacks(Window* window)
    {
        glfwSetCursorPosCallback(window->context(), PT::mouseCursorHandler);  
        glfwSetMouseButtonCallback(window->context(), PT::mouseButtonHandler);
        glfwSetScrollCallback(window->context(), PT::mouseScrollHandler);
    }

    void InputManager::setMouseHeld(bool torf)
    {
        mouseHeld = torf;
    }

    // TODO: Make sure no repeat keys unless specified?
    void InputManager::processInput(Window* window, GL::Renderer* renderer)
    {
        if (glfwGetKey(window->context(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window->context(), true);
        }

        if (glfwGetKey(window->context(), GLFW_KEY_Q) == GLFW_PRESS)
        {
            renderer->addParticle(1000);
        }

        dispatch(window);
    }

    bool InputManager::register_dispatch(const char* key_name, unsigned int key, InputReceiver* dispatch_to)
    {
        // Check if exists, if not add a new vector...
        if (dispatchers.find(key) == dispatchers.end()) {
            std::vector<InputReceiver*> a;
            a.reserve(1);
            dispatchers[key] = a;
        }

        dispatchers[key].push_back(dispatch_to);
        CORE_LOG_INFO("InputManager -> Registered {}", key_name);
        // TODO: Robust this up!
    }

    void InputManager::dispatch(Window* window)
    {
        for (auto const& d : dispatchers)
        {
            if (glfwGetKey(window->context(), d.first) == GLFW_PRESS)
            {
                for (auto r : d.second)
                {
                    r->receive_dispatched_input(d.first);
                }
            }
        }
    }
} // namespace Input

