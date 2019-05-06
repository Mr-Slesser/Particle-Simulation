#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../GL/GLSLProgram.h"
#include "../GL/Buffers/VertexBuffer.h"
#include "../GL/Buffers/IndexBuffer.h"
#include "../GL/Buffers/VertexArray.h"

namespace GL
{
    class GLRenderer
    {
    private:
        
    public:
        GLRenderer();
        ~GLRenderer();

        void clear() const;
        void draw(VertexArray* va, IndexBuffer* ib, GLSLProgram* program) const;
    };
    
} // GL

#endif /* GLRENDERER_H */
