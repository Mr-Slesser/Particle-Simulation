#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>
#include <vector>

#include "InputReceiver.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Window/Window.h"
#include "../Camera/CameraManager.h"

#include "../../OpenGL/Renderer.h"

#include "../GlobalConfiguration.h"

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

        std::map<unsigned int, std::vector<InputReceiver*>> dispatchers;

    public:
        static InputManager *get();
        ~InputManager();

        bool register_dispatch(const char* key_name, unsigned int key, InputReceiver* dispatch_to);
        void dispatch(Window* window);
        
        // TODO: Configure function.
        void registerMouseCallbacks(Window* window);

        void setMouseHeld(bool torf);

        const inline bool isMouseHeld() const { return mouseHeld; }
        const inline float getSensitivity() const { return sensitivity; }

        void processInput(Window* window, GL::Renderer* renderer);

    };

    static void mouseCursorHandler(GLFWwindow* m, double x, double y)
    {
        static float lX = 0.0f;
        static float lY = 0.0f;
        if (!GC::get()->getBool("GUI_HOVER"))
        {
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

    }

    static void mouseButtonHandler(GLFWwindow* m, int button, int action, int mods)
    {
        if (!GC::get()->getBool("GUI_HOVER"))
        {
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                if(GLFW_PRESS == action)
                    InputManager::get()->setMouseHeld(true);
                else if(GLFW_RELEASE == action)
                    InputManager::get()->setMouseHeld(false);
            }
        }
    }

    static void mouseScrollHandler(GLFWwindow* window, double xoffset, double yoffset)
    {
        if (!GC::get()->getBool("GUI_HOVER"))
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
    }

} // namespace Input

#endif /* INPUTMANAGER_HPP */
