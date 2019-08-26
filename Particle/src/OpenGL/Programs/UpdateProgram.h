#ifndef UPDATEPROGRAM_H
#define UPDATEPROGRAM_H

#include "Program.h"

#define VS_UPDATE PATH("Shaders/update.vertex")

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