#include "PCHeader.h"
#include "Window.h"

Window *Window::instance = nullptr;

void processInput(Window *window)
{
  if (glfwGetKey(window->Context(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	glfwSetWindowShouldClose(window->Context(), true);

  Camera *camera = window->GetCamera();
  if (glfwGetKey(window->Context(), GLFW_KEY_W) == GLFW_PRESS)
	camera->ChangePosition(camera->Front());
  if (glfwGetKey(window->Context(), GLFW_KEY_S) == GLFW_PRESS)
	camera->ChangePosition(-camera->Front());

  if (glfwGetKey(window->Context(), GLFW_KEY_Q) == GLFW_PRESS)
	camera->ChangePosition(camera->Up());
  if (glfwGetKey(window->Context(), GLFW_KEY_E) == GLFW_PRESS)
	camera->ChangePosition(-camera->Up());

  if (glfwGetKey(window->Context(), GLFW_KEY_A) == GLFW_PRESS)
	camera->ChangePosition(-glm::normalize(glm::cross(camera->Front(), camera->Up())));
  if (glfwGetKey(window->Context(), GLFW_KEY_D) == GLFW_PRESS)
	camera->ChangePosition(glm::normalize(glm::cross(camera->Front(), camera->Up())));
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
  bool hov = Window::instance->IsMouseOverGUI();
  if (!hov)
  {
	static float prevX = 0.0f;
	static float prevY = 0.0f;

	static bool firstMouse = true;
	if (Window::instance->IsLeftMouseHeld())
	{
	  if (firstMouse)
	  {
		prevX = xpos;
		prevY = ypos;
		firstMouse = false;
	  }

	  float xoffset = xpos - prevX;
	  float yoffset = prevY - ypos;

	  prevX = xpos;
	  prevY = ypos;

	  Window::instance->GetCamera()->YawPitch(xoffset, yoffset);
	}
	else
	{
	  firstMouse = true;
	}
  }
}

void mouse_button_callback(GLFWwindow *m, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT)
  {
	if (action == GLFW_PRESS)
	  Window::instance->SetLeftMouseHeld(true);
	else if (action == GLFW_RELEASE)
	  Window::instance->SetLeftMouseHeld(false);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void glfw_error_callback(int error, const char *description)
{
  CORE_LOG_CRITICAL("GLFW ERROR: code {} msg: {}", error, description);
}

/* ----------------------------------------------------------------------------- */

bool Window::Init(const WindowConfig _config)
{
  	config = _config;
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
	glfwSetCursorPosCallback(ctx, mouse_callback);
	glfwSetMouseButtonCallback(ctx, mouse_button_callback);

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
void Window::Clear()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::AttachCamera(Camera _camera)
{
  camera = _camera;
}

void Window::SwapBuffers()
{
  glfwSwapBuffers(ctx);
}

void Window::SetWireframeMode(bool to)
{
  config.wireframe = to;

  if (config.wireframe)
  {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else
  {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}