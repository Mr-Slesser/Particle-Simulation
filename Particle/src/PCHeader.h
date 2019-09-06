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
#define _DEBUG_DRAW 1

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
#include <queue>

// Include: ImGUI
#include "Headers/ImGUI.hpp"

// Includes: OpenGL
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Includes: GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"

#include "Core/GlobalConfiguration.h"
#include "Utility/Log.h"
#include "OpenGL/GLLog.h"
#include "Headers/OpenGL.hpp"

#include "Utility/Math/Mathf.h"
#include "Utility/Random/Random.h"

// Includes: Helpers
#include "Headers/Colors.hpp"

// Includes: Singletons
#include "Core/GlobalConfiguration.h"
#include "Core/Input/InputManager.h"

#endif /* PCHEADER_H */
