#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/stb_image.h"

GL::Texture::Texture(const char* filePath, GLenum _type)
    : ID(0), width(0), height(0), type(_type)
{
    GLCheck(glGenTextures(1, &ID));
    GLCheck(glBindTexture(type, ID));
    GLCheck(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCheck(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCheck(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCheck(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLCheck(glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        GLCheck(glGenerateMipmap(type));
    }
    else
    {
        GL_LOG_ERROR("Failed to load texture: {}", filePath);
    }
    stbi_image_free(data);
}

GL::Texture::~Texture()
{
    GLCheck(glDeleteTextures(1, &ID));
}

void GL::Texture::bind()
{
    GLCheck(glBindTexture(type, ID));
}

void GL::Texture::unbind()
{
    GLCheck(glBindTexture(type, 0));
}
