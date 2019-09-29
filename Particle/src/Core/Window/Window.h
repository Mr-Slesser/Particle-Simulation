#ifndef WINDOW_H
#define WINDOW_H

#include "../Camera/CameraManager.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void glfw_error_callback(int error, const char *description);

struct WindowConfig
{
    unsigned int width = 1366;
    unsigned int height = 768;
    bool wireframe = false;
    bool fullscreen = false;
    const char *title = "New Window";
    int major = 4;
    int minor = 1;

    WindowConfig() {}
    WindowConfig(unsigned int w, unsigned int h, bool wf, bool fs) : width(w), height(h), wireframe(wf), fullscreen(fs) {}
    WindowConfig(unsigned int w, unsigned int h, const char *t, int maj, int min) : width(w), height(h), title(t), major(maj), minor(min) {}
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

    GLFWwindow *context();
    unsigned int getWidth();
    unsigned int getHeight();

    void setWidth(unsigned int width);
    void setHeight(unsigned int height);

    void setGLVersion(const int major, const int minor);
};

#endif /* WINDOW_H */
