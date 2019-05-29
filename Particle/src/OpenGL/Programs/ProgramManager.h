#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include <vector>

#include "../OpenGL.h"

#include "UpdateProgram.h"

namespace GL
{
    enum PROGRAM_TYPE {
        UPDATE = 0,
        RENDER = 1
    };

    class ProgramManager
    {
    private:
        std::vector<UpdateProgram*> update_programs;
        std::vector<Program*> render_programs;

        unsigned int u_active;
        unsigned int r_active;

        void use_update(unsigned int i);
        void use_render(unsigned int i);

    public:
        ProgramManager();
        virtual ~ProgramManager();

        bool init();

        void use(PROGRAM_TYPE type, unsigned int i = 0);

        Program* get_active(PROGRAM_TYPE type);

        void add_update(const char* file);
        void add_render(const char* vertex, const char* fragment);
    };
    
} // namespace GL

#endif /* PROGRAMMANAGER_H */
