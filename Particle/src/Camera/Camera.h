#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO: Tidy up global access of this.

enum PROJECTION_TYPE
{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

// TODO: Default camera values, i.e. implement a reset camera key.
// TODO: Incorporate handlers / Input Manager Class

class Camera
{
protected:
    glm::mat4 projection;
    glm::mat4 lookAt;

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;

    float pitch = 0.0f;
    float yaw = -90.0f;

public:
    static Camera* instance;
    Camera(PROJECTION_TYPE t);
    virtual ~Camera();

    void setProjection(PROJECTION_TYPE t, float width, float height);
    glm::mat4& getProjection();

    glm::mat4& setLookAt(float x, float y, float z);
    glm::mat4& setLookAt(glm::vec3& _pos);
    glm::mat4& setLookAt();
    const glm::mat4& getLookAt();

    const glm::vec3& getPosition() { return pos; }
    void setPosition(glm::vec3 _pos);
    void addPosition(glm::vec3 _pos);
    void subtractPosition(glm::vec3 _pos);

    const glm::vec3& getFront() { return front; }

    const glm::vec3& getUp() { return up; }

    static Camera* getThis() {
        return instance;
    }

    void setPY(float y, float p) {
        pitch += p;
        yaw += y;

        if(pitch > 89.0f)
            pitch =  89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 f;
        f.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        f.y = sin(glm::radians(pitch));
        f.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        front = glm::normalize(f);

        setLookAt();
    }

    void setProjection(float fov)
    {
        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 200.0f);  
    }
};

#endif /* CAMERA_HPP */
