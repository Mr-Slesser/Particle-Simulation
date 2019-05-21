#include "GLRenderer.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/stb_image.h"

GL::GLRenderer::GLRenderer()
{

}

GL::GLRenderer::~GLRenderer()
{

}

// void GL::GLRenderer::init(unsigned int indices[6], Vertex v[4], int vsize) 
void GL::GLRenderer::init(Vertex v[4], int vsize) 
{
    program = new GLSLProgram();
    vao = new VAO();
    vbo = new VBO(v, vsize, GL_STATIC_DRAW);

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3);
    vbl.push<float>(4);
    vbl.push<float>(2);

    vao->addBuffer(program, *vbo, vbl);
    ib = new QuadIndexBuffer(GLRENDERER_INDICES_SIZE);

    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    GLCheck(glGenTextures(1, &texture));
    GLCheck(glBindTexture(GL_TEXTURE_2D, texture));
    // set the texture wrapping/filtering options (on the currently bound texture object)
    GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);)	
    GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load("Particle/Resources/Textures/pusheen.jpeg", &width, &height, &nrChannels, 0);
    if (data)
    {
        GLCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        GLCheck(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    program->use();
    GLCheck(glUniform1i(glGetUniformLocation(program->getID(), "texture0"), 0));
}

void GL::GLRenderer::viewMatrix(float& dt, Camera* cam)
{
    // TODO: Can only call if this progran is bound.
    // TODO: Camera to update this on change.
    view = cam->getLookAt();
    int viewLoc = glGetUniformLocation(program->getID(), "view");
    GLCheck(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
}

void GL::GLRenderer::projectionMatrix(float& dt, Camera* cam)
{
    // TODO: Can only call if this progran is bound.
    // TODO: Camera to update this on change.
    projection = cam->getProjection();
    int projectionLoc = glGetUniformLocation(program->getID(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void GL::GLRenderer::clear() const
{
    GLCheck(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
	GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::GLRenderer::draw(float& dt, Camera* cam)
{
    program->use();
    GLCheck(glUniform1i(glGetUniformLocation(program->getID(), "texture0"), 0));
    GLCheck(glActiveTexture(GL_TEXTURE0));
        
    GLCheck(glBindTexture(GL_TEXTURE_2D, texture));
    vao->bind();
    ib->bind();
    GLCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}