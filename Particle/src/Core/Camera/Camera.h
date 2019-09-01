#ifndef CAMERA_H
#define CAMERA_H

#include "CameraStructures.h"

// TODO: Default camera values, i.e. implement a reset camera key.
// TODO: Tidy up the camera!
// TODO: Handle 3D & 2D Cases

namespace PT
{
class Camera
{
protected:
    PROJECTION_TYPE type;

    glm::mat4 projection;
    glm::mat4 lookAt;
    CameraData c;
    float cSpeed;

public:
    Camera(PROJECTION_TYPE t, const CameraData &config = DEFAULT_CAMERA);
    virtual ~Camera() {}

    // SECTION: Accessors
    glm::mat4 &getProjection() { return projection; }
    glm::mat4 &getLookAt() { return lookAt; }
    glm::vec3 &getPosition() { return c.pos; }
    glm::vec3 &getFront() { return c.front; }
    glm::vec3 &getUp() { return c.up; }
    inline float getFOV() { return c.fov; }

    // SECTION: Mutators
    void setProjection(float width, float height);
    void setProjection(float _fov);

    void setLookAt();
    void setLookAt(float x, float y, float z);
    void setLookAt(glm::vec3 &_pos);

    void setPosition(glm::vec3 _pos);
    void addPosition(glm::vec3 _pos);
    void subtractPosition(glm::vec3 _pos);
    void updatePosition(glm::vec3 update_axis);

    void setFront(glm::vec3 _front);
    void setUp(glm::vec3 _up);

    void setPY(float y, float p);

    // SECTION: Others
    virtual void handle_input(CAM_INPUT_MAP action);
};
} // namespace PT

#endif /* CAMERA_HPP */
