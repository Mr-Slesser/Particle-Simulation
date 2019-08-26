#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "../Input/InputReceiver.h"

#include "CameraStructures.h"
#include "Camera2D.hpp"
#include "Camera3D.hpp"

namespace PT
{
class CameraManager : public InputReceiver
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
    bool registerCamera(const char *camera_name, SM_CAM_TYPE type, const CameraData &data = {});
    Camera *getCamera(const char *camera_name = "DEFAULT");

    void register_input_dispatch() override;
    void receive_dispatched_input(unsigned int key) override;
};

} // namespace PT

#endif /* CAMERAMANAGER_H */
