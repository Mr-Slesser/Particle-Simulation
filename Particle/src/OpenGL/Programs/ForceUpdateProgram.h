#ifndef FORCEUPDATEPROGRAM_H
#define FORCEUPDATEPROGRAM_H

#include "UpdateProgram.h"

#define VS_FORCE_UPDATE PATH("Shaders/force_update.vertex")

namespace GL
{
class ForceUpdateProgram : public UpdateProgram
{
public:
    ForceUpdateProgram();
    virtual ~ForceUpdateProgram();

    bool init(const char *vertexPath = VS_FORCE_UPDATE, const char *fragmentPath = "") override;

protected:
    bool generateShader(const char *filePath, int &id);
};
} // namespace GL

#endif /* FORCEUPDATEPROGRAM_H */
