#ifndef APP_H
#define APP_H

#include <cstdio>

#include "../OpenGL/OpenGL.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window/Window.h"
#include "../OpenGL/Renderer.h"
#include "GUI/GUILayer.h"

#include "Camera/CameraManager.h"
#include "Input/InputManager.h"


namespace PT
{
    class App
    {
    private:
        Window* window;
        GL::Renderer* renderer;
        GUILayer* gui;

    public:
        App();
        ~App();

        bool init();
        void run();

        void processInput();
    };

} // namespace PT

#endif /* APP_H */
