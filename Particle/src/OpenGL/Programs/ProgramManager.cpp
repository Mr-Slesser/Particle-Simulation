#include "PCHeader.h"
#include "ProgramManager.h"

namespace GL
{
ProgramManager::ProgramManager()
{
}

ProgramManager::~ProgramManager()
{
    for (auto p : programs)
    {
        delete p;
    }
    programs.clear();
}

bool ProgramManager::Init()
{
    programs.resize(PROGRAM_TYPE::SIZE, nullptr);

    // DEBUG PROGRAM
    programs[PROGRAM_TYPE::RENDER_DEBUG] = new DebugProgram();
    if (!programs[PROGRAM_TYPE::RENDER_DEBUG]->Init(PATH("Shaders/Debug/debug.vertex.glsl"), PATH("Shaders/Debug/debug.fragment.glsl")))
    {
        GL_LOG_CRITICAL("GL::ProgramManager::Init() -> Unable to init RENDER_DEBUG program.");
        return false;
    }

    // RENDER MESH PROGRAM
	programs[PROGRAM_TYPE::RENDER_MESH] = new Program();
	if (!programs[PROGRAM_TYPE::RENDER_MESH]->Init(PATH("Shaders/Mesh/mesh.vertex.glsl"), PATH("Shaders/Mesh/mesh.fragment.glsl")))
	{
	  GL_LOG_CRITICAL("GL::ProgramManager::Init() -> Unable to init RENDER_MESH program.");
	  return false;
	}

    return true;
}

void ProgramManager::Use(PROGRAM_TYPE type)
{
    if (!programs[type])
    {
        GL_LOG_CRITICAL("Use Program Call: Type {} has not been initialized!", type);
    }
    else
    {
      	active = type;
        programs[type]->Use();
    }
}

Program *ProgramManager::Active()
{
  if (active == PROGRAM_TYPE::ERROR)
  {
	GL_LOG_CRITICAL("GL::ProgramManager::Active() -> No active program");
	return nullptr;
  }

  return programs[active];
}

} // namespace GL
