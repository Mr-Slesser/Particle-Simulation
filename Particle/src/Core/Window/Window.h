#ifndef WINDOW_H
#define WINDOW_H

#include "Camera.h"

class Window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *m, int button, int action, int mods);
void processInput(Window *window);
void glfw_error_callback(int error, const char *description);

struct WindowConfig
{
  unsigned int width = 1366;
  unsigned int height = 768;
  bool wireframe = false;
  bool fullscreen = false;
  const char *title = "EEUB53";

  WindowConfig()
  {}
  WindowConfig(unsigned int w, unsigned int h, bool wf, bool fs) : width(w), height(h), wireframe(wf), fullscreen(fs)
  {}
  WindowConfig(unsigned int w, unsigned int h, const char *t) : width(w), height(h), title(t)
  {}
};

class Window
{
 private:
  struct WindowConfig config;
  GLFWwindow *ctx;
  Camera camera;
  bool mouseHeldLeft = false;
  bool mouseOverGUI = false;

 public:
  static Window *instance;

  Window()
  {
	Window::instance = this;
	DefaultConfig();
  }
  ~Window()
  {
	glfwDestroyWindow(ctx);
	glfwTerminate();
  }

  bool Init(const WindowConfig _config = {});

  void Clear();
  void SwapBuffers();

  void SetWireframeMode(bool to);
  void AttachCamera(Camera _camera);

  inline bool IsActive() { return !glfwWindowShouldClose(ctx); }
  inline void DefaultConfig() { config = {}; }
  inline GLFWwindow *Context() const { return ctx; }
  inline unsigned int GetWidth() const { return config.width; }
  inline unsigned int GetHeight() const { return config.height; }
  inline float AspectRatio() const { return (float) config.width / (float) config.height; }
  inline Camera *GetCamera() { return &camera; }
  inline void SetLeftMouseHeld(bool to) { mouseHeldLeft = to; }
  inline bool IsLeftMouseHeld() const { return mouseHeldLeft; }

  inline void SetMouseOverGUI(bool to) { mouseOverGUI = to; }
  inline bool IsMouseOverGUI() const { return mouseOverGUI; }

};

#endif /* WINDOW_H */
