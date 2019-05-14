#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include "Camera.h"

class Camera2D : public Camera
{
private:
    
public:
    Camera2D() : Camera(PROJECTION_TYPE::ORTHOGRAPHIC) {}
    ~Camera2D() {}
};

#endif /* CAMERA2D_HPP */
