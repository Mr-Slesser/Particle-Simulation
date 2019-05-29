#ifndef UPDATEPROGRAM_H
#define UPDATEPROGRAM_H

#include "Program.h"

#ifdef PT_WIN
    #define VS_UPDATE_PART "Resources/Shaders/basic.update"
    #define VS_UPDATE "Resources/Shaders/update.vertex"  
#else
    #define VS_UPDATE_PART "./Particle/Resources/Shaders/basic.update"
    #define VS_UPDATE "./Particle/Resources/Shaders/update.vertex"  
#endif

namespace GL
{
    class UpdateProgram : public Program
    {
    public:
        UpdateProgram();
        virtual ~UpdateProgram();

        bool init(const char* vertexPath = VS_UPDATE, const char* fragmentPath = "") override;
        bool ainit(const char* vertexPath = VS_UPDATE_PART);

    protected:
        bool generateShader(const char* filePath, int& id);

    };
} // GL

#endif /* PROGRAM_H */