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
    std::lock_guard<std::mutex> lockGuard(mutex);
    elements.push_back(element);
}

void DebugDatastore::addElement(DebugDatastoreElement element0, DebugDatastoreElement element1)
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    elements.push_back(element0);
    elements.push_back(element1);
}

} // namespace GL
