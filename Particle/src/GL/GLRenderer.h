#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLSLProgram.h"
#include "Buffers/VBO.h"
#include "Buffers/EBO.h"
#include "Buffers/VAO.h"
#include "../Renderables/Vertex.hpp"
#include "../Camera/Camera2D.hpp"
#include "../Camera/Camera3D.hpp"
namespace GL
{
    class GLRenderer
    {
    private:
        GLSLProgram* program;
        VBO* vbo;
        EBO* ebo;
        VAO* vao;
        
    public:
        GLRenderer();
        virtual ~GLRenderer();

        void init(unsigned int indices[6], Vertex v[4], int vsize);

        void clear() const;
        void draw(float &dt, Camera* cam) const;
    };
    
} // GL

#endif /* GLRENDERER_H */
