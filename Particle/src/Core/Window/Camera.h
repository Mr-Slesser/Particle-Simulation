#ifndef PARTICLE_PARTICLE_SRC_CORE_WINDOW_CAMERA_H_
#define PARTICLE_PARTICLE_SRC_CORE_WINDOW_CAMERA_H_

class Camera
{
 private:
  glm::vec3 position   = glm::vec3(0.0f, 0.0f,  200.0f);
  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 right;
  glm::vec3 up    = glm::vec3(0.0f, 1.0f,  0.0f);
  glm::vec3 worldUp   = glm::vec3(0.0f, 1.0f,  0.0f);

  float speed = 0.05f;
  float sensitivity = 0.5f;
  float yaw = -90.0f;
  float pitch = 0.0f;

  float fov = 45.0f;
  float near = 0.1f;
  float far = 10000.0f;

 private:
  void Update();

 public:
  Camera();
  virtual ~Camera();

  void ChangePosition(float by);
  void ChangePosition(glm::vec3 by);
  void YawPitch(float _yaw, float _pitch);

  inline glm::mat4 View() { return glm::lookAt(position, position + front, up); }
  inline glm::mat4 Projection(float aspect) { return glm::perspective(glm::radians(fov), aspect, near, far); }

  inline glm::vec3 Position() { return position; }
  inline glm::vec3 Front() { return front; }
  inline glm::vec3 Up() { return up; }
};

#endif //PARTICLE_PARTICLE_SRC_CORE_WINDOW_CAMERA_H_
