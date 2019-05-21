#ifndef VBO_H
#define VBO_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GL
{
    class VBO 
    {
    private:
        unsigned int ID;

    public:
        VBO(const void* _data, unsigned int _size, int _draw = GL_STATIC_DRAW);
        virtual ~VBO();

        void bind() const;
        void unbind() const;
    };  
} // GL

#endif /* VBO_H */
