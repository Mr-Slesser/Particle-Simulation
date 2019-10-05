#ifndef PARTICLE_PARTICLE_SRC_OPENGL_BUFFERS_NOISETBO_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_BUFFERS_NOISETBO_H_

namespace GL
{
class NoiseTBO
{
 private:
  unsigned int bufferID;
  unsigned int bufferTextureID;
  GLenum textureUnit;

 public:
  NoiseTBO(GLenum _textureUnit, std::vector<glm::vec3> &_noise);
  virtual ~NoiseTBO();

  void bindTexture();
  void loadData(glm::vec3 *pointer, int size);

  glm::vec3 *getPointer();
  void releasePointer();
};
}


#endif //PARTICLE_PARTICLE_SRC_OPENGL_BUFFERS_NOISETBO_H_
