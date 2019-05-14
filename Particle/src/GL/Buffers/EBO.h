#ifndef EBO_H
#define EBO_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GL
{
    class EBO
    {
    private:
        unsigned int ID;
        unsigned int count;

    public:
        EBO(const unsigned int* _data, unsigned int _count, int _draw = GL_STATIC_DRAW);
        virtual ~EBO();

        inline unsigned int getCount() { return count; }
        void bind() const;
        void unbind() const;
    };
} // GL

#endif /* EBO_H */