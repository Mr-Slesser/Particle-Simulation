#include "Camera.h"

namespace PT
{
    Camera::Camera(PROJECTION_TYPE t, const CameraData& config)
        : c(config), type(t), cSpeed(5.0f)
    {
        lookAt = glm::lookAt(c.pos, c.pos + c.front, c.up);
        // TODO: These values need to be from GC!!!
        setProjection(1366.0f, 768.0f);
    }

    // SECTION: Mutators
    void Camera::setProjection(float width, float height)
    {
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
        projection = glm::perspective(glm::radians(c.fov), 800.0f / 600.0f, 0.1f, 100000.0f);  
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

    void Camera::setLookAt(glm::vec3& _pos)
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

    void Camera::updatePosition(glm::vec3 update_axis) {
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

    void Camera::setPY(float y, float p) {
        c.pitch += p;
        c.yaw += y;

        if(c.pitch > 89.0f)
            c.pitch =  89.0f;
        if(c.pitch < -89.0f)
            c.pitch = -89.0f;

        glm::vec3 f;
        f.x = cos(glm::radians(c.pitch)) * cos(glm::radians(c.yaw));
        f.y = sin(glm::radians(c.pitch));
        f.z = cos(glm::radians(c.pitch)) * sin(glm::radians(c.yaw));
        c.front = glm::normalize(f);

        setLookAt();
    }

    // SECTION: Others
    void Camera::handle_input(CAM_INPUT_MAP action)
    {
        CORE_LOG_WARN("Camera -> Unimplemented Input Handler!");
    }
}