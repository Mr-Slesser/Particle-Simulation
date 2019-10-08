#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "../Programs/ProgramManager.h"
#include "../Datastores/DebugData.h"

namespace GL
{

class DebugRenderer
{
protected:
  	std::shared_ptr<ProgramManager> programs;
  	std::shared_ptr<DebugData> datastore;

private:
public:
    DebugRenderer();
    virtual ~DebugRenderer();

    bool Init(std::shared_ptr<ProgramManager> _programs, std::shared_ptr<DebugData> _datastore);
    void Draw();
};

} // namespace GL

#endif /* DEBUGRENDERER_H */
