#ifndef DEBUGDATA_H
#define DEBUGDATA_H

namespace GL
{

struct DebugDataElement
{
    glm::vec3 position;
    glm::vec4 colour = Colour::WHITE;
};

class DebugData
{
private:
    std::vector<DebugDataElement> elements;

public:
    DebugData();
    ~DebugData();

    void addElement(DebugDataElement element);
    inline std::vector<DebugDataElement> getElements() { return elements; }
    inline void beginDebug() { elements.clear(); }
};

} // namespace GL

#endif /* DEBUGDATA_H */
