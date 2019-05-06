#ifndef APP_H
#define APP_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../Window/Window.h"
#include "../GL/GLSLProgram.h"

class App
{
private:
    Window* window;
    GL::GLSLProgram* program;

    unsigned int VBO;
    unsigned int VAO;
    float dt;

    float vertices[9] = {
        -0.25f, -0.25f, 0.0f, // left  
        0.25f, -0.25f, 0.0f, // right
        0.0f,  0.25f, 0.0f  // top   
    };

public:
    App();
    ~App();

    void init();
    void run();
};

#endif /* APP_H */
