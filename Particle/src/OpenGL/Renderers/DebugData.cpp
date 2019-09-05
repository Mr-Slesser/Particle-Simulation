#include "PCHeader.h"
#include "DebugData.h"

namespace GL
{

DebugData::DebugData()
{
}

DebugData::~DebugData()
{
    elements.clear();
    elements.resize(100000);
}

void DebugData::addElement(DebugDataElement element)
{
    elements.push_back(element);
}

} // namespace GL
