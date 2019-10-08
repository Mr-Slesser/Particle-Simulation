#ifndef PROGRAM_H
#define PROGRAM_H

namespace GL
{
class Program
{
protected:
    unsigned int ID;
    std::map<const char *, int> uniform_locations;
    virtual bool CompileShader(const char *filePath, int &id);

public:
    Program();
    virtual ~Program();

    virtual bool Init(const char *vertexPath, const char *fragmentPath);

    void Use();

    unsigned int GetID() const { return ID; }
    int UniformLocation(const char *name);

    // SECTION: Uniform helper functions.
    void Bool(const char *name, bool value);
    void Int(const char *name, int value);
    void Float(const char *name, float value);
    void Double(const char *name, double value);
    void Vec2(const char *name, const glm::vec2 &value);
    void Vec2(const char *name, float x, float y);
    void Vec3(const char *name, const glm::vec3 &value);
    void Vec3(const char *name, float x, float y, float z);
    void Vec4(const char *name, const glm::vec4 &value);
    void Vec4(const char *name, float x, float y, float z, float w);
    void Mat2(const char *name, const glm::mat2 &mat);
    void Mat3(const char *name, const glm::mat3 &mat);
    void Mat4(const char *name, const glm::mat4 &mat);
};
} // namespace GL

#endif /* PROGRAM_H */
