#ifndef DEBUGDATASTORE_H
#define DEBUGDATASTORE_H

namespace GL
{

struct DebugDatastoreElement
{
    glm::vec3 position;
    glm::vec4 colour = Colour::WHITE;
};

class DebugDatastore
{
private:
    std::vector<DebugDatastoreElement> elements;

public:
    DebugDatastore();
    ~DebugDatastore();

    void addElement(DebugDatastoreElement element);
    inline std::vector<DebugDatastoreElement> getElements() { return elements; }
    inline void beginDebug() { elements.clear(); }
};

} // namespace GL

#endif /* DEBUGDATASTORE_H */
