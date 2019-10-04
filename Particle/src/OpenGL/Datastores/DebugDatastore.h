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
    std::mutex mutex;

public:
    DebugDatastore();
    ~DebugDatastore();

    void addElement(DebugDatastoreElement element);
    void addElement(DebugDatastoreElement element0, DebugDatastoreElement element1);
    inline std::vector<DebugDatastoreElement> getElements() { return elements; }
    int dataSize() { return elements.size(); }
};

} // namespace GL

#endif /* DEBUGDATASTORE_H */
