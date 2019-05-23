#ifndef APP_H
#define APP_H

// TODO: Add logging to all areas.
// TODO: Review Namespaces & Align
// TODO: Key sequernce logger. i.e. log to file.

#include "../OpenGL/OpenGL.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera/CameraManager.h"
#include "Input/InputManager.h"
#include "Window/Window.h"

#include "../OpenGL/Renderer.h"

#include <cstdio>

namespace PT
{
    class App
    {
    private:
        Window* window;
        GL::Renderer* renderer;

    public:
        App();
        ~App();

        bool init();
        void run();

        void processInput();
    };

} // namespace PT

#endif /* APP_H */
