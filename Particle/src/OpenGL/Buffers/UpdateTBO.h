#ifndef PARTICLE_PARTICLE_SRC_OPENGL_BUFFERS_UPDATETBO_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_BUFFERS_UPDATETBO_H_

namespace GL
{
  class UpdateTBO
  {
   private:
	unsigned int bufferID;
	unsigned int bufferTextureID;
	GLenum textureUnit;

   public:
	UpdateTBO(GLenum _textureUnit, std::vector<glm::vec3> &_force);
	virtual ~UpdateTBO();

	void bindTexture();
	void loadData(glm::vec3 *pointer, int size);

	glm::vec3* getPointer();
	void releasePointer();
  };
}
#endif //PARTICLE_PARTICLE_SRC_OPENGL_BUFFERS_UPDATETBO_H_
