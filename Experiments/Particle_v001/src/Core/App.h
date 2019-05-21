#ifndef APP_H
#define APP_H

// TODO: Start up info print.

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera/CameraManager.h"
#include "Input/InputManager.h"
#include "Window/Window.h"
#include "../GL/GLRenderer.h"
#include "../Renderables/Quad.hpp"

#include <cstdio>

namespace PT
{
    class App
    {
    private:
        Window* window;
        GL::GLRenderer* renderer;
        Quad q;
        float dt;

    public:
        App();
        ~App();

        void init();
        void run();

        void processInput();
    };

} // namespace PT

#endif /* APP_H */
