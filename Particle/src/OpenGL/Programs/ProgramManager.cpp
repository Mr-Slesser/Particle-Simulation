#include "ProgramManager.h"

namespace GL
{
ProgramManager::ProgramManager()
    : u_active(0), r_active(0)
{
}

ProgramManager::~ProgramManager()
{
    for (auto p : update_programs)
    {
        delete p;
    }
    update_programs.clear();

    for (auto p : render_programs)
    {
        delete p;
    }
    render_programs.clear();
}

bool ProgramManager::init()
{
    update_programs.push_back(new UpdateProgram());
    if (!update_programs.back()->ainit())
    {
        GL_LOG_CRITICAL("GL::ProgramManager::init() -> Unable to init default update program.");
        return false;
    }
    Print_All(update_programs.back()->getID());

    render_programs.push_back(new Program());
    if (!render_programs.back()->init())
    {
        GL_LOG_CRITICAL("GL::ProgramManager::init() -> Unable to init default render program.");
        return false;
    }
    Print_All(render_programs.back()->getID());

    return true;
}

void ProgramManager::use(PROGRAM_TYPE type, unsigned int i)
{
    if (type == UPDATE)
    {
        use_update(i);
    }
    else if (type == RENDER)
    {
        use_render(i);
    }
}

Program *ProgramManager::get_active(PROGRAM_TYPE type)
{
    if (type == UPDATE)
    {
        return update_programs[u_active];
    }
    else if (type == RENDER)
    {
        return render_programs[r_active];
    }
}

void ProgramManager::add_update(const char *file)
{
    update_programs.push_back(new UpdateProgram());
    if (!update_programs.back()->init(file))
    {
        GL_LOG_WARN("GL::ProgramManager::add_update() -> Unable to add program.");
        update_programs.pop_back();
    }
}

void ProgramManager::add_render(const char *vertex, const char *fragment)
{
    render_programs.push_back(new Program());
    if (!render_programs.back()->init(vertex, fragment))
    {
        GL_LOG_WARN("GL::ProgramManager::add_render() -> Unable to add program.");
        render_programs.pop_back();
    }
}

void ProgramManager::use_update(unsigned int i)
{
    if (i >= update_programs.size())
    {
        GL_LOG_ERROR("Use Update Program Call: Index {} is invalid, maximum index is: {}, using index 0.", i, update_programs.size() - 1);
        update_programs[0]->use();
        u_active = 0;
    }

    update_programs[i]->use();
    u_active = i;
}

void ProgramManager::use_render(unsigned int i)
{
    if (i >= render_programs.size())
    {
        GL_LOG_ERROR("Use Render Program Call: Index {} is invalid, maximum index is: {}, using index 0.", i, render_programs.size() - 1);
        render_programs[0]->use();
        r_active = 0;
    }

    render_programs[i]->use();
    r_active = i;
}

} // namespace GL
