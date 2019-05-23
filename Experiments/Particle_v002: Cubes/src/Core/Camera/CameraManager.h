#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <map>
#include <cassert>

#include "../../Utility/Log.h"

#include "Camera2D.hpp"
#include "Camera3D.hpp"

namespace PT
{
    enum SM_CAM_TYPE {
        cam2D,
        cam3D
    };

    class CameraManager
    {
    private:
        static CameraManager* instance;
        std::map<const char*, Camera*> cameras;

        CameraManager();

        bool initCameras();

    public:
        ~CameraManager();
        static CameraManager *get();


        bool startup();

        bool registerCamera(const char* camera_name, SM_CAM_TYPE type, const CameraData& data = {});

        Camera* getCamera(const char* camera_name = "DEFAULT");
    };
    
} // namespace PT

#endif /* CAMERAMANAGER_H */
