#ifndef VAO_H
#define VAO_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "VBO.h"
#include "VBOLayout.h"

namespace GL
{
    class VAO
    {
    private:
        unsigned int ID;

    public:
        VAO();
        virtual ~VAO();

        void addBuffer(const VBO& vb, const VBOLayout& layout);
        void bind() const;
        void unbind() const;
    };
    
} // GL

#endif /* VAO_H */
