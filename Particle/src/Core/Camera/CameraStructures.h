#ifndef CAMERASTRUCTURES_H
#define CAMERASTRUCTURES_H

#include "PCHeader.h"
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

static const CameraData DEFAULT_CAMERA = {
    0.0f, -90.0f, 45.0f,
    glm::vec3(0.0f, 0.0f, 400.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)};
} // namespace PT

#endif /* CAMERASTRUCTURES_H */
