#ifndef APP_H
#define APP_H

// TODO: Start up info print.
// TODO: Test framework

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../Window/Window.h"
#include "../GL/GLSLProgram.h"
#include "../GL/Buffers/VertexBuffer.h"
#include "../GL/Buffers/IndexBuffer.h"
#include "../GL/Buffers/VertexArray.h"
#include "../GL/GLRenderer.h"

class App
{
private:
    Window* window;
    GL::GLSLProgram* program;
    GL::VertexBuffer* vb;
    GL::IndexBuffer* ib;
    GL::VertexArray* va;
    GL::GLRenderer* renderer;

    float dt;

    float vertices[12] = {
        -0.25f, -0.25f, 0.0f,   // 0
        0.25f, -0.25f, 0.0f,    // 1
        0.25f,  0.25f, 0.0f,    // 2
        -0.25f,  0.25f, 0.0f    // 3
    };

    unsigned int indices[6] = {
        0, 1, 2, 
        2, 3, 0
    };

public:
    App();
    ~App();

    void init();
    void run();

    void processInput();
};

#endif /* APP_H */
