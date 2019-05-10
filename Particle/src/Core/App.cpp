#include "App.h"

App::App()
    : dt(0.0f)
{
    init();
}

App::~App()
{
    glfwTerminate();
}

void App::init()
{
    window = new Window();
    window->init();
    program = new GL::GLSLProgram();

    v[0] = {{-0.25f, -0.65f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}};
    v[1] = {{0.25f, -0.25f, 0.0f},  {0.0f, 1.0f, 1.0f, 1.0f}};
    v[2] = {{0.25f,  0.25f, 0.0f},  {1.0f, 1.0f, 1.0f, 1.0f}};
    v[3] = {{-0.25f,  0.25f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}};

    
    va = new GL::VertexArray();
    //vb = new GL::VertexBuffer(vertices, 4 * 3 * sizeof(float), GL_STATIC_DRAW);
    vb = new GL::VertexBuffer(v, sizeof(v), GL_STATIC_DRAW);

    GL::VertexBufferLayout vbl = GL::VertexBufferLayout();
    vbl.push<float>(3);
    vbl.push<float>(4);

    va->addBuffer(*vb, vbl);
    ib = new GL::IndexBuffer(indices, 6, GL_STATIC_DRAW);
    renderer = new GL::GLRenderer();
}

void App::run()
{
    while (window->isActive())
	{
        dt += 0.01;
		
        renderer->clear();
        processInput();
        program->use();
        program->setFloat("time", dt);
        renderer->draw(va, ib, program);

		glfwSwapBuffers(window->context());
		glfwPollEvents();
	}
}

void App::processInput()
{
	if (glfwGetKey(window->context(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
		glfwSetWindowShouldClose(window->context(), true);
    }
}