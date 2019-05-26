#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum PROJECTION_TYPE
{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

// TODO: Default camera values, i.e. implement a reset camera key.
// TODO: Tidy up the camera!

struct CameraData
{
    float pitch;
    float yaw;
    float fov;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
};

static const CameraData DEFAULT_CAMERA = { 
    0.0f, -90.0f, 45.0f, 
    glm::vec3(0.0f, 0.0f,  3.0f), 
    glm::vec3(0.0f, 0.0f, -1.0f), 
    glm::vec3(0.0f, 1.0f,  0.0f)
};

class Camera
{
protected:
    PROJECTION_TYPE type;
    glm::mat4 projection;
    glm::mat4 lookAt;

    CameraData c;

public:
    static Camera* instance;
    Camera(PROJECTION_TYPE t, const CameraData& config = DEFAULT_CAMERA);
    virtual ~Camera();

    void setProjection(float width, float height);
    glm::mat4& getProjection();

    glm::mat4& setLookAt(float x, float y, float z);
    glm::mat4& setLookAt(glm::vec3& _pos);
    glm::mat4& setLookAt();
    glm::mat4& getLookAt();

    glm::vec3& getPosition() { return c.pos; }
    void setPosition(glm::vec3 _pos);
    void addPosition(glm::vec3 _pos);
    void subtractPosition(glm::vec3 _pos);

    glm::vec3& getFront() { return c.front; }

    glm::vec3& getUp() { return c.up; }

    static Camera* getThis() {
        return instance;
    }

    inline float getFOV() { return c.fov; }
    void setPY(float y, float p) {
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

    void setProjection(float _fov)
    {
        c.fov = _fov;
        projection = glm::perspective(glm::radians(c.fov), 800.0f / 600.0f, 0.1f, 100000.0f);  
    }
};

#endif /* CAMERA_HPP */
