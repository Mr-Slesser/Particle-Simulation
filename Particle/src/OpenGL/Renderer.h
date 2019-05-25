#ifndef RENDERER_H
#define RENDERER_H

#include <cstdlib>
#include <math.h>
#include <vector>

#include "OpenGL.h"
#include "Program.h"
#include "VertexArray.h"
#include "VertexData.h"
#include "Texture.h"

#include "../Particle/Particle.h"

#include "../Primitives/Quad.h"
#include "../Primitives/Cube.h"
#include "../Core/Camera/CameraManager.h"
#include "../Primitives/Quad.h"

#include "../Utility/Math.h"

#define VS_POINT "./Particle/Resources/Shaders/point.vertex"
#define FS_POINT "./Particle/Resources/Shaders/point.fragment"

#define ZERO_MEM(a) memset(a, 0, sizeof(a))

namespace GL
{
    class Renderer
    {
    private:
        const int MAX_PARTICLES = 1000000;
        const int total = 50;
        Program* program;
        
        VertexData vd;

        VertexArray* va;
        VBPointer* pointer;

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        std::vector<PT::Particle*> particles;


    public:
        Renderer();
        ~Renderer();

        bool init();
        void clear();
        void draw();

        void update();

        void modelMatrix();
        void viewMatrix();
        void projectionMatrix();

        void changeShaders(int type);
    };
    
} // namespace GL


#endif /* RENDERER_H */
