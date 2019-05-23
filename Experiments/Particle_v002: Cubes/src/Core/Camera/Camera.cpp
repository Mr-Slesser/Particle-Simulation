#include "Camera.h"

Camera* Camera::instance = 0;

Camera::Camera(PROJECTION_TYPE t, const CameraData& config)
    : c(config), type(t)
{
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
    setProjection(1366.0f, 768.0f); 
    instance = this;
}

Camera::~Camera()
{

}

void Camera::setProjection(float width, float height)
    {
        if (type == PROJECTION_TYPE::PERSPECTIVE)
        {
            projection = glm::perspective(glm::radians(45.0f), (width / height), 0.1f, 5000.0f);
        }      
        else if (type == PROJECTION_TYPE::ORTHOGRAPHIC)
        {
            projection = glm::ortho(-width / 2, width / 2, -width / 2, height / 2, 0.1f, 5000.0f);
        }
    }

glm::mat4& Camera::getProjection()
{
    return projection;
}

glm::mat4& Camera::setLookAt(float x, float y, float z)
{
    c.pos = glm::vec3(x, y, z);
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
    return lookAt;
}

glm::mat4& Camera::setLookAt(glm::vec3& _pos)
{
    c.pos = _pos;
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
    return lookAt;
}

glm::mat4& Camera::setLookAt()
{
    lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
    return lookAt;
}

glm::mat4& Camera::getLookAt()
{
    return lookAt;
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