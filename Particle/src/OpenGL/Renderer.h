#ifndef RENDERER_H
#define RENDERER_H

#include "OpenGL.h"
#include "Program.h"
#include "VertexArray.h"
#include "Texture.h"

#include "../Primitives/Quad.h"
#include "../Core/Camera/CameraManager.h"

#define TEXTURE_LOC "./Particle/Resources/Textures/pusheen.jpeg"

#define VS_TEST "./Particle/Resources/Shaders/test.vertex"
#define FS_TEST "./Particle/Resources/Shaders/test.fragment"

namespace GL
{
    class Renderer
    {
    private:
        Program* program;
        VertexArray* va;
        Texture* t;
        
        unsigned int texture;

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        Quad q;

    public:
        Renderer();
        ~Renderer();

        void init();
        void clear();
        void draw();

        void modelMatrix();
        void viewMatrix();
        void projectionMatrix();

        void changeShaders(int type);
    };
    
} // namespace GL


#endif /* RENDERER_H */
