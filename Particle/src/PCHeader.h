#ifndef PCHEADER_H
#define PCHEADER_H

// Defines
#ifdef PT_WIN
#define PATH(x) "Resources/" x
#else
#define PATH(x) "./Particle/Resources/" x
#endif

// Math Defines
#define PI 3.14159265
#define HALF_PI PI / 2

#define _PROFILER_FILE_LOG 1

// Includes
#include <assert.h>
#include <chrono>
#include <cstdio>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

// Include: ImGUI
#include "Headers/ImGUI.hpp"
// #include "Headers/imgui/imgui.h"
// #include "Headers/imgui/imgui_impl_glfw.h"
// #include "Headers/imgui/imgui_impl_opengl3.h"

// Includes: OpenGL
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Includes: GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/GlobalConfiguration.h"
#include "Utility/Log.h"
#include "OpenGL/GLLog.h"
#include "Headers/OpenGL.hpp"

// Includes: Helpers
#include "Headers/Colors.hpp"

// Includes: Singletons
#include "Core/GlobalConfiguration.h"
#include "Core/Input/InputManager.h"

#endif /* PCHEADER_H */
