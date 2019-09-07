#include "PCHeader.h"
#include "DebugDatastore.h"

namespace GL
{

DebugDatastore::DebugDatastore()
{
}

DebugDatastore::~DebugDatastore()
{
    elements.clear();
    elements.resize(100000);
}

void DebugDatastore::addElement(DebugDatastoreElement element)
{
    elements.push_back(element);
}

void DebugDatastore::beginDebug()
{
    PROFILE("DebugDatastore::beginDebug");

    elements.clear();
}

} // namespace GL
