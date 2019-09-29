#ifndef CAMERA_H
#define CAMERA_H

namespace PT
{
#define CAM_INPUT_DEF_FILE "../../../Resources/Definitions/Input-Camera.def"

enum CAM_INPUT_MAP
{
#define CAM_INPUT_DEF(x, y) x = y,
#include CAM_INPUT_DEF_FILE
#undef CAM_INPUT_DEF
};

enum SM_CAM_TYPE
{
  cam2D,
  cam3D
};

enum PROJECTION_TYPE
{
  PERSPECTIVE,
  ORTHOGRAPHIC
};

struct CameraData
{
  float pitch;
  float yaw;
  float fov;
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;
};

static const PT::CameraData DEFAULT_CAMERA = {
	0.0f, -90.0f, 45.0f,
	glm::vec3(250.0f, 250.0f, 500.0f),
	glm::vec3(0.0f, -1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
};

class Camera
{
protected:
    PROJECTION_TYPE type;

    glm::mat4 projection;
    glm::mat4 lookAt;
 	CameraData c;
    float cSpeed;
    float width;
    float height;

public:
    Camera(PROJECTION_TYPE t, const CameraData &config = DEFAULT_CAMERA);
    virtual ~Camera() {}

    void setProjection(float _width, float _height);
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


    virtual void handle_input(CAM_INPUT_MAP action);

    inline float getSpeed() { return cSpeed; }
	inline glm::mat4 &getProjection() { return projection; }
	inline glm::mat4 &getLookAt() { return lookAt; }
	inline glm::vec3 &getPosition() { return c.pos; }
	inline glm::vec3 &getFront() { return c.front; }
	inline glm::vec3 &getUp() { return c.up; }
	inline float getFOV() { return c.fov; }
};

} // namespace PT

#endif /* CAMERA_HPP */
