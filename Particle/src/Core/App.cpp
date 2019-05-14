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

    v[0] = {{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}};
    v[1] = {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}};
    v[2] = {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
    v[3] = {{-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}};

    renderer = new GL::GLRenderer();
    renderer->init(indices, v, sizeof(v));

    //cam = new Camera2D();
    cam = new Camera3D();

    window->registerMouseCursorHandler(App::mouseCursorHandler, App::mouseButtonHandler, App::mouseScrollHandler);
}

void App::run()
{
    while (window->isActive())
	{
        dt += 0.01;
		
        renderer->clear();
        processInput();
        renderer->draw(dt, cam);

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

    float cSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window->context(), GLFW_KEY_W) == GLFW_PRESS)
        cam->addPosition(cSpeed * cam->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_S) == GLFW_PRESS)
        cam->subtractPosition(cSpeed * cam->getFront());
    if (glfwGetKey(window->context(), GLFW_KEY_A) == GLFW_PRESS)
        cam->subtractPosition(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cSpeed);
    if (glfwGetKey(window->context(), GLFW_KEY_D) == GLFW_PRESS)
        cam->addPosition(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cSpeed);
}

// NOTE: Static
static bool firstMouse = true;
static int mouseHeld = false;
void App::mouseCursorHandler(GLFWwindow* m, double x, double y)
{
    static float lX = 400.0f;
    static float lY = 300.0f;

    if (mouseHeld)
    {
        if(firstMouse) // this bool variable is initially set to true
        {
            lX = x;
            lY = y;
            firstMouse = false;
        }
        // TODO: Use this to wrap a functor!

        float xoffset = x - lX;
        float yoffset = lY - y; // reversed since y-coordinates range from bottom to top
        lX = x;
        lY = y;

        static float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        Camera::getThis()->setPY(xoffset, yoffset);
    }
}

void App::mouseButtonHandler(GLFWwindow* m, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if(GLFW_PRESS == action)
            mouseHeld = true;
        else if(GLFW_RELEASE == action)
            mouseHeld = false;
    }
}

static float fov = 45.0f;
void App::mouseScrollHandler(GLFWwindow* window, double xoffset, double yoffset)
{
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;

    Camera::getThis()->setProjection(fov);
}