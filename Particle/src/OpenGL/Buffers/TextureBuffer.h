#ifndef PARTICLE_TEXTUREBUFFER_H
#define PARTICLE_TEXTUREBUFFER_H

class TextureBuffer {
private:
    unsigned int bufferID;
    unsigned int bufferTextureID;
    GLenum textureUnit;

public:
    TextureBuffer(GLenum _textureUnit);
    virtual ~TextureBuffer();

    void bindTexture();
    void loadData();

    glm::vec3* getPointer();
    void releasePointer();
};

#endif //PARTICLE_TEXTUREBUFFER_H
