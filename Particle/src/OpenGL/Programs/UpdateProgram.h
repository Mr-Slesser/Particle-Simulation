#ifndef UPDATEPROGRAM_H
#define UPDATEPROGRAM_H

#include "Program.h"

namespace GL
{
class UpdateProgram : public Program
{
public:
    UpdateProgram();
    virtual ~UpdateProgram();

    virtual bool init(const char *vertexPath, const char *fragmentPath = "") override;
};
} // namespace GL

#endif /* PROGRAM_H */