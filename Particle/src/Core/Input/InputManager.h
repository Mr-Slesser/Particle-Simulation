#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Window/Window.h"
#include "../Camera/Camera.h"

// TODO: Handlers to be created, using an input config singleton as a bridge.

namespace PT::Input
{
    class InputManager
    {
    private:
        static InputManager* instance;
        InputManager();

        // Mouse
        bool mouseHeld;
        float sensitivity;

    public:
        static InputManager *get();
        ~InputManager();

        // TODO: Configure function.
        void registerMouseCallbacks(Window* window);

        void setMouseHeld(bool torf);


        const inline bool isMouseHeld() const;
        const inline float getSensitivity() const;
    };

        static void mouseCursorHandler(GLFWwindow* m, double x, double y)
    {
        static float lX = 400.0f;
        static float lY = 300.0f;

        if (InputManager::get()->isMouseHeld())
        {
            static bool firstMouse = true;
            if (firstMouse)
            {
                lX = x;
                lY = y;
                firstMouse = false;
            }

            float xoffset = x - lX;
            float yoffset = lY - y;
            lX = x;
            lY = y;

            xoffset *= InputManager::get()->getSensitivity();
            yoffset *= InputManager::get()->getSensitivity();

            Camera::getThis()->setPY(xoffset, yoffset);
        }
    }

    static void mouseButtonHandler(GLFWwindow* m, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if(GLFW_PRESS == action)
                InputManager::get()->setMouseHeld(true);
            else if(GLFW_RELEASE == action)
                InputManager::get()->setMouseHeld(false);
        }
    }

    static void mouseScrollHandler(GLFWwindow* window, double xoffset, double yoffset)
    {
        float fov = Camera::getThis()->getFOV();
        if(fov >= 1.0f && fov <= 45.0f)
            fov -= yoffset;
        if(fov <= 1.0f)
            fov = 1.0f;
        if(fov >= 45.0f)
            fov = 45.0f;

        Camera::getThis()->setProjection(fov);
    }

} // namespace Input

#endif /* INPUTMANAGER_HPP */
