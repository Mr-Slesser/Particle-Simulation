#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include "UpdateProgram.h"
#include "DebugProgram.h"

namespace GL
{
enum PROGRAM_TYPE
{
    UPDATE = 0,
    RENDER,
    RENDER_DEBUG,
    RENDER_MESH,
    SIZE
};

class ProgramManager
{
private:
    std::vector<Program *> programs;

public:
    ProgramManager();
    virtual ~ProgramManager();

    bool init();

    void use(PROGRAM_TYPE type, unsigned int i = 0);

    Program *get_active(PROGRAM_TYPE type);
};

} // namespace GL

#endif /* PROGRAMMANAGER_H */
