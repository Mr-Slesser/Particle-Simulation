#ifndef WINDOW_H
#define WINDOW_H

#include "../Camera/CameraManager.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void glfw_error_callback(int error, const char *description);

/* NOTE: Class to contain:
    - Window size values as vector
*/

struct WindowConfig
{
    unsigned int width = 1366;
    unsigned int height = 768;
    bool wireframe = false;
    const char *title = "New Window";
    int major = 4;
    int minor = 1;

    WindowConfig()
    {
    }
    WindowConfig(unsigned int w, unsigned int h, const char *t, int maj, int min)
        : width(w), height(h), title(t), major(maj), minor(min) {}
};

class Window
{
private:
    struct WindowConfig config;
    GLFWwindow *ctx;

public:
    Window(const WindowConfig _config = {});
    ~Window();

    GLFWwindow *init();
    bool isActive();
    void defaultConfig();

    // SECTION: Accessors
    GLFWwindow *context();
    unsigned int getWidth();
    unsigned int getHeight();

    // SECTION: Mutators
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);

    // SECTION: Hint functions
    void setGLVersion(const int major, const int minor);
};

#endif /* WINDOW_H */
