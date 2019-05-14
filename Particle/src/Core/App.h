#ifndef APP_H
#define APP_H

// TODO: Start up info print.
// TODO: PT Namespace
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window/Window.h"
#include "../GL/GLRenderer.h"
#include "../Renderables/Vertex.hpp"

#include "Input/InputManager.h"

#include "Camera/Camera2D.hpp"
#include "Camera/Camera3D.hpp"

class App
{
private:
    Window* window;
    GL::GLRenderer* renderer;
    Vertex v[4];
    Camera* cam;
    float dt;


    float vertices[12] = {
        -0.25f, -0.25f, 0.0f,   // 0
        0.25f, -0.25f, 0.0f,    // 1
        0.25f,  0.25f, 0.0f,    // 2
        -0.25f,  0.25f, 0.0f    // 3
    };

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
    // static void mouseCursorHandler(GLFWwindow* m, double x, double y);
    // static void mouseButtonHandler(GLFWwindow* m, int button, int action, int mods);
    // static void mouseScrollHandler(GLFWwindow* window, double xoffset, double yoffset);
};

#endif /* APP_H */
