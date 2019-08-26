#ifndef TEXTURE_H
#define TEXTURE_H

namespace GL
{

class Texture
{
public:
    Texture(const char *filePath, GLenum _type);
    virtual ~Texture();

    inline unsigned int getID() const { return ID; }

    void bind();
    void unbind();

private:
    unsigned int ID;
    int width;
    int height;
    unsigned int type;
};
} // namespace GL

#endif /* TEXTURE_H */
