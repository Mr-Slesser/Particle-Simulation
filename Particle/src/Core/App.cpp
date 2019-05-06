#include "App.h"

App::App()
    : VBO(0), VAO(0), dt(0.0f)
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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // REVIEW: Needed?
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void App::run()
{
    while (window->isActive())
	{
        dt += 0.01;
		window->processInput();


		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program->use();
        program->setFloat("time", dt);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glPointSize(5.0);
		glDrawArrays(GL_POINTS, 0, 3);

		glfwSwapBuffers(window->context());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}