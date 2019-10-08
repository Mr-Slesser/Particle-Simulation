#include "PCHeader.h"
#include "Camera.h"

Camera::Camera()
{
  Update();
}

Camera::~Camera()
{

}

void Camera::Update()
{
  glm::vec3 _front;
  _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  _front.y = sin(glm::radians(pitch));
  _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(_front);

  right = glm::normalize(glm::cross(front, worldUp));
  up    = glm::normalize(glm::cross(right, front));
}

void Camera::ChangePosition(float by)
{
  position += by * speed;
}

void Camera::ChangePosition(glm::vec3 by)
{
  position += by * speed;
}

void Camera::YawPitch(float _yaw, float _pitch)
{
  _yaw *= sensitivity;
  _pitch *= sensitivity;

  yaw   += _yaw;
  pitch += _pitch;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  Update();
}
