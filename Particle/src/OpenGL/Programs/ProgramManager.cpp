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

bool ProgramManager::init()
{
    programs.resize(PROGRAM_TYPE::SIZE, nullptr);

    // UPDATE PROGRAM
    programs[PROGRAM_TYPE::UPDATE] = new UpdateProgram();
    if (!programs[PROGRAM_TYPE::UPDATE]->init(PATH("Shaders/particle_update.vertex.glsl")))
    {
        GL_LOG_CRITICAL("GL::ProgramManager::init() -> Unable to init UPDATE program.");
        return false;
    }
    Print_All(programs[PROGRAM_TYPE::UPDATE]->getID());

    // UPDATE FORCE PROGRAM
	programs[PROGRAM_TYPE::UPDATE_FORCE] = new ForceUpdateProgram();
	if (!programs[PROGRAM_TYPE::UPDATE_FORCE]->init(PATH("Shaders/Forces/force.update.vertex.glsl")))
	{
	  GL_LOG_CRITICAL("GL::ProgramManager::init() -> Unable to init UPDATE_FORCE program.");
	  return false;
	}
	Print_All(programs[PROGRAM_TYPE::UPDATE_FORCE]->getID());

    // RENDER PROGRAM
    programs[PROGRAM_TYPE::RENDER] = new Program();
    if (!programs[PROGRAM_TYPE::RENDER]->init())
    {
        GL_LOG_CRITICAL("GL::ProgramManager::init() -> Unable to init RENDER program.");
        return false;
    }
    Print_All(programs[PROGRAM_TYPE::RENDER]->getID());

    // DEBUG PROGRAM
    programs[PROGRAM_TYPE::RENDER_DEBUG] = new DebugProgram();
    if (!programs[PROGRAM_TYPE::RENDER_DEBUG]->init(PATH("Shaders/Debug/debug.vertex.glsl"), PATH("Shaders/Debug/debug.fragment.glsl")))
    {
        GL_LOG_CRITICAL("GL::ProgramManager::init() -> Unable to init RENDER_DEBUG program.");
        return false;
    }
    Print_All(programs[PROGRAM_TYPE::RENDER_DEBUG]->getID());

    // RENDER MESH PROGRAM
	programs[PROGRAM_TYPE::RENDER_MESH] = new Program();
	if (!programs[PROGRAM_TYPE::RENDER_MESH]->init(PATH("Shaders/mesh.vertex.glsl"), PATH("Shaders/mesh.fragment.glsl")))
	{
	  GL_LOG_CRITICAL("GL::ProgramManager::init() -> Unable to init RENDER_MESH program.");
	  return false;
	}
	Print_All(programs[PROGRAM_TYPE::RENDER_MESH]->getID());

    return true;
}

void ProgramManager::use(PROGRAM_TYPE type, unsigned int i)
{
    if (!programs[type])
    {

        GL_LOG_CRITICAL("Use Program Call: Type {} has not been initialized!", type);
    }
    else
    {
        programs[type]->use();
    }
}

Program *ProgramManager::get_active(PROGRAM_TYPE type)
{
    return programs[type];
}

} // namespace GL
