#include "PCHeader.h"
#include "Window.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  PT::Camera *cam = PT::CameraManager::get()->getCamera();
  cam->setProjection(width, height);
  glViewport(0, 0, width, height);
}

void glfw_error_callback(int error, const char *description)
{
  CORE_LOG_CRITICAL("GLFW ERROR: code {} msg: {}", error, description);
}

/* ----------------------------------------------------------------------------- */

bool Window::Init()
{
    CORE_LOG_INFO("Starting GLFW: {}", glfwGetVersionString());
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        CORE_LOG_CRITICAL("Window: could not start GLFW");
        return false;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    ctx = glfwCreateWindow(config.width, config.height, config.title, config.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    if (ctx == NULL)
    {
        CORE_LOG_CRITICAL("Window: GLFWwindow init failure");
        return false;
    }

    glfwMakeContextCurrent(ctx);
    glfwSetFramebufferSizeCallback(ctx, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        CORE_LOG_CRITICAL("Window: GLAD init failure");
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);

    return true;
}