#ifndef PARTICLE_PARTICLE_SRC_SIMULATION_VORTEX_H_
#define PARTICLE_PARTICLE_SRC_SIMULATION_VORTEX_H_

namespace PT
{
class Vortex
{
 private:
  glm::ivec3 position;
  float speed;
  float scale;

 public:
  Vortex(const glm::ivec3 &position, float speed, int scale);
  virtual ~Vortex();

  const glm::ivec3 &GetPosition() const;
  void SetPosition(const glm::ivec3 &position);

  float GetSpeed() const;
  void SetSpeed(float speed);

  int GetScale() const;
  void SetScale(int scale);
};
}
#endif //PARTICLE_PARTICLE_SRC_SIMULATION_VORTEX_H_
