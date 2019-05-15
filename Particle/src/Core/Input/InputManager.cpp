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

    const bool InputManager::isMouseHeld() const
    {
        return mouseHeld;
    }

    const float InputManager::getSensitivity() const
    {
        return sensitivity;
    }

} // namespace Input

