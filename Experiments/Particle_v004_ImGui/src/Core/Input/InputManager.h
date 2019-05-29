#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Window/Window.h"
#include "../Camera/CameraManager.h"
// TODO: Handlers to be created, using an input config singleton as a bridge.

namespace PT
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

        const inline bool isMouseHeld() const { return mouseHeld; }
        const inline float getSensitivity() const { return sensitivity; }
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

            CameraManager::get()->getCamera()->setPY(xoffset, yoffset);
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
        float fov = CameraManager::get()->getCamera()->getFOV();
        if(fov >= 1.0f && fov <= 45.0f)
            fov -= yoffset;
        if(fov <= 1.0f)
            fov = 1.0f;
        if(fov >= 45.0f)
            fov = 45.0f;

        CameraManager::get()->getCamera()->setProjection(fov);
    }

} // namespace Input

#endif /* INPUTMANAGER_HPP */
