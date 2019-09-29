#include "PCHeader.h"
#include "Camera.h"

namespace PT
{
Camera::Camera(PROJECTION_TYPE t, const CameraData &config)
    : c(config), type(t), cSpeed(2.0f), width(1366.0f), height(768.0f)
{
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
    setProjection(1366.0f, 768.0f);
}

void Camera::setProjection(float _width, float _height)
{
    width = _width;
    height = _height;

    if (type == PROJECTION_TYPE::PERSPECTIVE)
    {
        projection = glm::perspective(glm::radians(45.0f), (width / height), 0.1f, 100000.0f);
    }
    else if (type == PROJECTION_TYPE::ORTHOGRAPHIC)
    {
        projection = glm::ortho(-width / 2, width / 2, -width / 2, height / 2, 0.1f, 100000.0f);
    }
}

void Camera::setProjection(float _fov)
{
    c.fov = _fov;
    projection = glm::perspective(glm::radians(c.fov), width / height, 0.1f, 100000.0f);
}

void Camera::setLookAt()
{
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
}

void Camera::setLookAt(float x, float y, float z)
{
    c.pos = glm::vec3(x, y, z);
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
}

void Camera::setLookAt(glm::vec3 &_pos)
{
    c.pos = _pos;
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
}

void Camera::setPosition(glm::vec3 _pos)
{
    c.pos = _pos;
    setLookAt();
}

void Camera::addPosition(glm::vec3 _pos)
{
    c.pos += _pos;
    setLookAt();
}

void Camera::subtractPosition(glm::vec3 _pos)
{
    c.pos -= _pos;
    setLookAt();
}

void Camera::updatePosition(glm::vec3 update_axis)
{
    c.pos += (update_axis * cSpeed);
    setLookAt();
}

void Camera::setFront(glm::vec3 _front)
{
    c.front = _front;
    setLookAt();
}

void Camera::setUp(glm::vec3 _up)
{
    c.up = _up;
    setLookAt();
}

void Camera::setPY(float y, float p)
{
    c.pitch += p;
    c.yaw += y;

    if (c.pitch > 89.0f)
        c.pitch = 89.0f;
    if (c.pitch < -89.0f)
        c.pitch = -89.0f;

    glm::vec3 f;
    f.x = cos(glm::radians(c.pitch)) * cos(glm::radians(c.yaw));
    f.y = sin(glm::radians(c.pitch));
    f.z = cos(glm::radians(c.pitch)) * sin(glm::radians(c.yaw));
    c.front = glm::normalize(f);

    setLookAt();
}

void Camera::handle_input(CAM_INPUT_MAP action)
{
  switch(action)
  {
	case LEFT:      // SECTION:: LEFT (-X)
	  updatePosition(glm::vec3(-1.0f, 0.0f, 0.0f));
	  break;
	case RIGHT:     // SECTION: RIGHT (+X)
	  updatePosition(glm::vec3(1.0f, 0.0f, 0.0f));
	  break;
	case UP:        // SECTION: UP (+Z)
	  updatePosition(glm::vec3(0.0f, 0.0f, -1.0f));
	  break;
	case DOWN:      // SECTION: DOWN (-Z)
	  updatePosition(glm::vec3(0.0f, 0.0f, 1.0f));
	  break;
	case RAISE:
	  updatePosition(glm::vec3(0.0f, 1.0f, 0.0f));
	  break;
	case LOWER:
	  updatePosition(glm::vec3(0.0f, -1.0f, 0.0f));
	  break;
	default:
	  std::string r;
	  switch (action) {
#define CAM_INPUT_DEF(x, y) case y: r = #x; break;
#include CAM_INPUT_DEF_FILE
#undef CAM_INPUT_DEF
	  }
	  CORE_LOG_WARN("Camera2D -> Unimplemented input action [{}]", r);
	  break;
  }
}
} // namespace PT