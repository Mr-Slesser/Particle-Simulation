#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include "DebugProgram.h"

namespace GL
{
enum PROGRAM_TYPE
{
    RENDER_DEBUG = 0,
    RENDER_MESH,
    SIZE,
    ERROR
};

class ProgramManager
{
private:
    std::vector<Program *> programs;
  	PROGRAM_TYPE active = PROGRAM_TYPE::ERROR;

public:
    ProgramManager();
    virtual ~ProgramManager();
    bool Init();
    void Use(PROGRAM_TYPE type);
    Program *Active();
};

} // namespace GL

#endif /* PROGRAMMANAGER_H */
