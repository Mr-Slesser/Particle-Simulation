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
#include "../Renderables/Vertex.hpp"

namespace PT
{
    class App
    {
    private:
        Window* window;
        GL::GLRenderer* renderer;
        Vertex v[4];
        float dt;

        unsigned int indices[6] = {
            0, 1, 3, 
            1, 2, 3
        };

    public:
        App();
        ~App();

        void init();
        void run();

        void processInput();
    };

} // namespace PT

#endif /* APP_H */
