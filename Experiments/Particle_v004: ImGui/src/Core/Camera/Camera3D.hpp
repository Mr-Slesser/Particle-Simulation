#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#include "Camera.h"

class Camera3D : public Camera
{
private:
    
public:
    Camera3D() : Camera(PROJECTION_TYPE::PERSPECTIVE) {}
    ~Camera3D() {}
};

#endif /* CAMERA3D_HPP */
