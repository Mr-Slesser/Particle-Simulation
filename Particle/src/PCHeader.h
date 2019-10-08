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
#define TWO_PI PI * 2

#define _PROFILER_FILE_LOG 1
#define _DEBUG_DRAW 1

// Includes
#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

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
#include "Utility/Profiler.h"
#include "OpenGL/GLLog.h"
#include "Headers/OpenGL.hpp"

#include "Utility/Math/Mathf.h"
#include "Utility/Random/Random.h"
#include "Utility/Random/Perlin.h"

// Includes: Helpers
#include "Headers/Colors.hpp"
#include "Core/Window/Window.h"

#endif /* PCHEADER_H */
