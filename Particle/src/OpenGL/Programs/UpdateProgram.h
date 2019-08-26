#ifndef UPDATEPROGRAM_H
#define UPDATEPROGRAM_H

#include "Program.h"

#ifdef PT_WIN
#define VS_UPDATE "Resources/Shaders/update.vertex"
#else
#define VS_UPDATE "./Particle/Resources/Shaders/update.vertex"
#endif

namespace GL
{
class UpdateProgram : public Program
{
public:
    UpdateProgram();
    virtual ~UpdateProgram();

    bool init(const char *vertexPath = VS_UPDATE, const char *fragmentPath = "") override;

protected:
    bool generateShader(const char *filePath, int &id);
};
} // namespace GL

#endif /* PROGRAM_H */