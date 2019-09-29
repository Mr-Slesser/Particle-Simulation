#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Camera.h"

namespace PT
{

class CameraManager
{
private:
    static CameraManager *instance;
    std::map<const char *, Camera *> cameras;

    CameraManager();

    bool initCameras();

public:
    ~CameraManager();
    static CameraManager *get();

    bool startup();
    bool registerCamera(const char *camera_name, const CameraData &data = {});
    Camera *getCamera(const char *camera_name = "DEFAULT");

    void register_input_dispatch();
    void receive_dispatched_input(unsigned int key);
};

} // namespace PT

#endif /* CAMERAMANAGER_H */
