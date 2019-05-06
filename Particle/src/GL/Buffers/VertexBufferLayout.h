#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GL   
{
    struct VBElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int getSizeOfType(unsigned int type)
        {
            switch(type)
            {
                case GL_FLOAT:          return 4;
                case GL_UNSIGNED_INT:   return 4;
                case GL_UNSIGNED_BYTE:  return 1;
            }
            return 0;
        }
    };

    class VertexBufferLayout
    {
    private:
        std::vector<VBElement> elements;
        unsigned int stride;

    public:
        VertexBufferLayout()
            : stride(0) {}

        template<typename T>
        void push(unsigned int count)
        {
            // TODO: Fail here... warning?
        }

        inline const std::vector<VBElement> getElements() const { return elements; }
        inline unsigned int getStride() const { return stride; }
    };

    template<>
    inline void VertexBufferLayout::push<float>(unsigned int count)
    {
        elements.push_back({GL_FLOAT, count, GL_FALSE});
        stride += count * VBElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    inline void VertexBufferLayout::push<unsigned int>(unsigned int count)
    {
        elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        stride += count * VBElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    inline void VertexBufferLayout::push<unsigned char>(unsigned int count)
    {
        elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        stride += count * VBElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }

} // GL

#endif /* VERTEXBUFFERLAYOUT_H */
