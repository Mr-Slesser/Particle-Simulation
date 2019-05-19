#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLSLProgram.h"
#include "Buffers/VBO.h"
#include "Buffers//IndexBuffer/QuadIndexBuffer.hpp"
#include "Buffers/VAO.h"

#include "../Renderables/Vertex.hpp"
#include "../Core/Camera/Camera2D.hpp"
#include "../Core/Camera/Camera3D.hpp"

#include "../Renderables/Quad.hpp"

#define GLRENDERER_MAX_QUADS	100
#define GLRENDERER_QUAD_SIZE	sizeof(Vertex) * 4
#define GLRENDERER_BUFFER_SIZE	GLRENDERER_QUAD_SIZE * GLRENDERER_MAX_QUADS
#define GLRENDERER_INDICES_SIZE GLRENDERER_MAX_QUADS * 6

namespace GL
{
    class GLRenderer
    {
    private:
        GLSLProgram* program;
        VBO* vbo;
        IndexBuffer* ib;
        VAO* vao;

        // TODO: Model matrix vector.
        glm::mat4 view;
        glm::mat4 projection;
        
    public:
        GLRenderer();
        virtual ~GLRenderer();

        void init(Vertex v[4], int vsize);

        void modelMatrix(float& dt, Camera* cam);
        void viewMatrix(float& dt, Camera* cam);
        void projectionMatrix(float& dt, Camera* cam);

        void clear() const;
        void draw(float &dt, Camera* cam);
    };
    
} // GL

#endif /* GLRENDERER_H */
