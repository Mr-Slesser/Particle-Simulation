#include "Window.h"

Window::Window(const WindowConfig _config)
    : config(_config)
{
}

Window::~Window()
{
}

GLFWwindow* Window::init()
{
    assert(restart_gl_log());
    gl_log("Starting GLFW\n%s\n", glfwGetVersionString());
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW\n");
        // TODO: Error!
    }
    setGLVersion(config.major, config.minor);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);  
    ctx = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);

	if (ctx == NULL)
	{
        FATAL(Error::TYPE::WINDOW_CREATION_FAIL, "Failed to initialise window");
        return nullptr;
	}

	glfwMakeContextCurrent(ctx);
	glfwSetFramebufferSizeCallback(ctx, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
        FATAL(Error::TYPE::WINDOW_GLAD_FAIL, "Failed to initialise GLAD");
        return nullptr;
	}
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    log_gl_params();
    return ctx;
}

bool Window::isActive()
{
    return !glfwWindowShouldClose(ctx);
}

void Window::defaultConfig()
{
    config = {};
}

// SECTION: Accessors
GLFWwindow* Window::context()
{
    return ctx;
}

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

// SECTION: Callbacks.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // TODO: Update camera values too.
    // TODO: Size and width need to be global
	glViewport(0, 0, width, height);
}

void glfw_error_callback(int error, const char* description)
{
    gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}