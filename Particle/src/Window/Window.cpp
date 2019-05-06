#include "Window.h"

Window::Window(const WindowConfig _config)
    : config(_config)
{
}

Window::~Window()
{
    glfwTerminate();
    window = nullptr;
}

GLFWwindow* Window::get()
{
    return window;
}

GLFWwindow* Window::init()
{
	glfwInit();
    setGLVersion(config.major, config.minor);

    window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);

	if (window == NULL)
	{
        FATAL(Error::TYPE::WINDOW_CREATION_FAIL, "Failed to initialise window");
        return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
        FATAL(Error::TYPE::WINDOW_GLAD_FAIL, "Failed to initialise GLAD");
        return nullptr;
	}

    return window;
}

bool Window::isActive()
{
    return !glfwWindowShouldClose(window);
}

void Window::defaultConfig()
{
    config = {};
}

void Window::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// SECTION: Accessors
unsigned int Window::getWidth()
{
    return config.width;
}

unsigned int Window::getHeight()
{
    return config.height;
}

// SECTION: Mutators
void Window::setWidth(unsigned int _width)
{
    config.width = _width;
}

void Window::setHeight(unsigned int _height)
{
    config.height = _height;
}

// SECTION: Hint Functions
void Window::setGLVersion(const int major, const int minor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}