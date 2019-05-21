#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define TEXTURE_LOC "./Particle/Resources/Textures/fireworks_red.jpg"

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    unsigned char* m_image;
};

#endif	/* TEXTURE_H */
