#ifndef PTRENDERER_H
#define PTRENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PTProgram.h"

#include "../GL/GLSLProgram.h"
#include "../GL/Buffers/VBO.h"
#include "../GL/Buffers//IndexBuffer/QuadIndexBuffer.hpp"
#include "../GL/Buffers/VAO.h"

//#include "../Renderables/Vertex.hpp"
#include "../Core/Camera/Camera2D.hpp"
#include "../Core/Camera/Camera3D.hpp"

//#include "../Renderables/Quad.hpp"

#define PTRENDERER_MAX_POINTS	5000
#define PTRENDERER_POINT_SIZE	sizeof(Vertex) * 4
#define PTRENDERER_BUFFER_SIZE	PTRENDERER_QUAD_SIZE * PTRENDERER_MAX_POINTS
#define PTRENDERER_INDICES_SIZE PTRENDERER_MAX_POINTS * 6

namespace PT
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
    };

    class PTRenderer
    {
    private:
        PTProgram* update_program;
        PTProgram* render_program;

        unsigned int vao[2];
        unsigned int vbo[2];
        unsigned int tbo;

        int model_matrix_loc;
        int projection_matrix_loc;
        int triangle_count_loc;
        int time_step_loc;

        int render_model_matrix_loc;
        int render_projection_matrix_loc;

        unsigned int geometry_vbo;
        unsigned int render_vao;
        unsigned int geometry_tex;

        // TODO: Model matrix vector.
        glm::mat4 view;
        glm::mat4 projection;
        
    public:
        PTRenderer();
        virtual ~PTRenderer();

        void init();

        void modelMatrix(float& dt, Camera* cam);
        void viewMatrix(float& dt, Camera* cam);
        void projectionMatrix(float& dt, Camera* cam);

        void clear() const;
        void draw(float &dt, Camera* cam);

        Vertex vertices[3] = 
        {
            {glm::vec3(-0.5f, 0.5f, 0.0f),    glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(0.5f, 0.0f, 0.0f),     glm::vec3(0.0f, 0.0f, -1.0f)}
        };
    };
    
} // PT

#endif /* PTRENDERER_H */
