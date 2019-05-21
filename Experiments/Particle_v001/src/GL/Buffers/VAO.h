#ifndef VAO_H
#define VAO_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "VBOLayout.h"
#include "../GLSLProgram.h"

namespace GL
{
    class VAO
    {
    private:
        unsigned int ID;

    public:
        VAO();
        virtual ~VAO();

        void addBuffer(const GLSLProgram* program, const VBO& vb, const VBOLayout& layout);
        void bind() const;
        void unbind() const;
    };
    
} // GL

#endif /* VAO_H */
