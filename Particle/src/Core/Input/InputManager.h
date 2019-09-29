#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "InputReceiver.h"
#include "../Window/Window.h"
#include "../../Simulation/Simulation.h"
#include "../Camera/CameraManager.h"
#include "../../OpenGL/Renderers/Renderer.h"

namespace PT
{
class InputManager
{
 private:
  static InputManager *instance;
  InputManager();

  // Mouse
  bool mouseHeld;
  float sensitivity;

  unsigned int particleFloodAmount;

  std::map<unsigned int, std::vector<InputReceiver *>> dispatchers;

 public:
  static InputManager *get();
  ~InputManager();

  bool register_dispatch(const char *key_name, unsigned int key, InputReceiver *dispatch_to);
  void dispatch(Window *window);

  void registerMouseCallbacks(Window *window);

  void setMouseHeld(bool torf);

  const inline bool isMouseHeld() const
  { return mouseHeld; }
  const inline float getSensitivity() const
  { return sensitivity; }

  inline void setParticleFloodAmount(int to) { particleFloodAmount = to; }

  void processInput(Window *window, GL::Renderer *renderer, PT::Simulation *simulation);
};

static void mouseCursorHandler(GLFWwindow *m, double x, double y)
{
  static float lX = 0.0f;
  static float lY = 0.0f;
  if (!GC::get()->getBool("GUI_HOVER"))
  {
	static bool firstMouse = true;
	if (InputManager::get()->isMouseHeld())
	{
	  if (firstMouse)
	  {
		lX = x;
		lY = y;
		firstMouse = false;
	  }

	  float xoffset = x - lX;
	  float yoffset = lY - y;

	  //float xoffset =  (0.0f < x) - (x < 0.0f); // Gets sign... -1, 0, 1
	  //float yoffset =  (0.0f < y) - (y < 0.0f);

	  lX = x;
	  lY = y;

	  xoffset *= InputManager::get()->getSensitivity();
	  yoffset *= InputManager::get()->getSensitivity();

	  CameraManager::get()->getCamera()->setPY(xoffset, yoffset);
	} else
	{
	  firstMouse = true;
	}
  }
}

static void mouseButtonHandler(GLFWwindow *m, int button, int action, int mods)
{
  if (!GC::get()->getBool("GUI_HOVER"))
  {
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
	  if (GLFW_PRESS == action)
		InputManager::get()->setMouseHeld(true);
	  else if (GLFW_RELEASE == action)
		InputManager::get()->setMouseHeld(false);
	}
  }
}

static void mouseScrollHandler(GLFWwindow *window, double xoffset, double yoffset)
{
  if (!GC::get()->getBool("GUI_HOVER"))
  {
	auto camera = CameraManager::get()->getCamera();
	auto cspeed = camera->getSpeed();
	camera->addPosition((float) (yoffset * cspeed) * camera->getFront());
  }
}

} // namespace PT

#endif /* INPUTMANAGER_HPP */
