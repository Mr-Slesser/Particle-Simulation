#ifndef RENDERER_H
#define RENDERER_H

#include "OpenGL.h"
#include "Program.h"
#include "VertexArray.h"
#include "Texture.h"

#include "../Primitives/Quad.h"
#include "../Primitives/Cube.h"
#include "../Core/Camera/CameraManager.h"

#define TEXTURE_LOC "./Particle/Resources/Textures/pusheen.jpeg"
//#define TEXTURE_LOC "./Particle/Resources/Textures/sprite.png"

#define VS_TEST "./Particle/Resources/Shaders/test.vertex"
#define FS_TEST "./Particle/Resources/Shaders/test.fragment"

#define VS_POINT "./Particle/Resources/Shaders/point.vertex"
#define FS_POINT "./Particle/Resources/Shaders/point.fragment"

#define VS_POINTS "./Particle/Resources/Shaders/pointSprite.vertex"
#define FS_POINTS "./Particle/Resources/Shaders/pointSprite.fragment"

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

        glm::vec3 cubePositions[10] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };


        //Quad q;
        Cube q;

    public:
        Renderer();
        ~Renderer();

        bool init();
        void clear();
        void draw();

        void modelMatrix();
        void viewMatrix();
        void projectionMatrix();

        void changeShaders(int type);
    };
    
} // namespace GL


#endif /* RENDERER_H */
