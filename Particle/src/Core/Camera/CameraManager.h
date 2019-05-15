#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <map>

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
        std::map<char*, Camera*> cameras;

        CameraManager();

        //bool initInputManager();
        bool initCameras();

    public:
        ~CameraManager();
        static CameraManager *get();


        bool startup();

        bool registerCamera(char* camera_name, SM_CAM_TYPE type, const CameraData& data = {});

        Camera* getCamera(char* camera_name = "DEFAULT");
    };
    
} // namespace PT

#endif /* CAMERAMANAGER_H */
