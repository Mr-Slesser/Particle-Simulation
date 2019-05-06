#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "./../Utility/Error.hpp"

/* NOTE: Class to contain:
    - Act as a wrapper, so in future if needed to not use GLFW etc. then could easily switch
    - wireframe mode: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    - Window size values as vector
    - Chain hints / setters toge
    - Input class
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct WindowConfig {
    unsigned int width = 800;
    unsigned int height = 600;
    bool wireframe = false;
    const char * title = "New Window";
    int major = 3;
    int minor = 3;

    WindowConfig() {}
    WindowConfig(unsigned int w, unsigned int h, const char* t, int maj, int min)
        : width(w), height(h), title(t), major(maj), minor(min) {}
};

class Window
{
private:
    struct WindowConfig config;
    GLFWwindow* ctx;

public:
    Window(const WindowConfig _config = {});
    ~Window();

    GLFWwindow* init();
    bool isActive();
    void defaultConfig();
    void processInput();

    // SECTION: Accessors
    GLFWwindow* context();
    unsigned int getWidth();
    unsigned int getHeight();

    // SECTION: Mutators
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);

    // SECTION: Hint functions
    void setGLVersion(const int major, const int minor);
};

#endif /* WINDOW_H */
