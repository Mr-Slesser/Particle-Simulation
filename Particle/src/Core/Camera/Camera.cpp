#include "Camera.h";

Camera* Camera::instance = 0;

Camera::Camera(PROJECTION_TYPE t)
{
    pos = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f,  0.0f);

    lookAt = glm::lookAt(pos, pos + front, up);
    setProjection(t, 800.0f, 600.0f); 

    instance = this;
}

Camera::~Camera()
{

}

void Camera::setProjection(PROJECTION_TYPE t, float width, float height)
    {
        if (t == PROJECTION_TYPE::PERSPECTIVE)
        {
            projection = glm::perspective(glm::radians(45.0f), (width / height), 0.1f, 200.0f);
        }      
        else if (t == PROJECTION_TYPE::ORTHOGRAPHIC)
        {
            projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 0.1f, 100.0f);
        }
    }

glm::mat4& Camera::getProjection()
{
    return projection;
}

glm::mat4& Camera::setLookAt(float x, float y, float z)
{
    pos = glm::vec3(x, y, z);
    lookAt = glm::lookAt(pos, pos + front, up);
    return lookAt;
}

glm::mat4& Camera::setLookAt(glm::vec3& _pos)
{
    pos = _pos;
    lookAt = glm::lookAt(pos, pos + front, up);
    return lookAt;
}

glm::mat4& Camera::setLookAt()
{
    lookAt = glm::lookAt(pos, pos + front, up);
    return lookAt;
}

glm::mat4& Camera::getLookAt()
{
    return lookAt;
}

void Camera::setPosition(glm::vec3 _pos)
{
    pos = _pos;
    setLookAt();
}

void Camera::addPosition(glm::vec3 _pos)
{
    pos += _pos;
    setLookAt();
}

void Camera::subtractPosition(glm::vec3 _pos)
{
    pos -= _pos;
    setLookAt();
}