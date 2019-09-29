#ifndef WINDOW_H
#define WINDOW_H

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void glfw_error_callback(int error, const char *description);

struct WindowConfig
{
    unsigned int width = 1366;
    unsigned int height = 768;
    bool wireframe = false;
    bool fullscreen = false;
    const char *title = "New Window";

    WindowConfig() {}
    WindowConfig(unsigned int w, unsigned int h, bool wf, bool fs) : width(w), height(h), wireframe(wf), fullscreen(fs) {}
    WindowConfig(unsigned int w, unsigned int h, const char *t) : width(w), height(h), title(t) {}
};

class Window
{
private:
    struct WindowConfig config;
    GLFWwindow *ctx;

public:
    Window(const WindowConfig _config = {}) : config(_config) {}
    ~Window() {}

    bool Init();

    inline bool IsActive() { return !glfwWindowShouldClose(ctx); }
    inline void DefaultConfig() { config = {}; }
    inline GLFWwindow *Context() const { return ctx; }
    inline unsigned int GetWidth() const { return config.width; }
    inline unsigned int GetHeight() const { return config.height; }

};

#endif /* WINDOW_H */
