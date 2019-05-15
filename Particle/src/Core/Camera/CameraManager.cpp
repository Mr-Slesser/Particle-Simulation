#include "CameraManager.h"

// SECTION: Private functions
PT::CameraManager *PT::CameraManager::instance = 0;

PT::CameraManager *PT::CameraManager::get()
{
    if (!instance)
        instance = new PT::CameraManager;
    return instance;
}

    // : inputMgr(nullptr)
PT::CameraManager::CameraManager()
{
    // REVIEW: Do we want to actually pass params to this, so make it a separate function?
    if(startup())
    {
        // Log success?
    }
    else
    {
        // TODO: Error.
    }
}

bool PT::CameraManager::initCameras()
{
    // By default create the default camera!
    if (!registerCamera("DEFAULT", cam3D))
    {
        // TODO: Handle 
    }
    return true;
}

// SECTION: Public functions
PT::CameraManager::~CameraManager()
{
    for (auto ele: cameras)
    {
        delete ele.second;
        ele.second = nullptr;
    }
}

bool PT::CameraManager::startup()
{
    if (initCameras()) {
        // Log success?
    } else {
        // TODO: Error.
        return false;
    }
    
    return true;
}

bool PT::CameraManager::registerCamera(char* camera_name, SM_CAM_TYPE type, const CameraData& data)
{
    // TODO: Handle data!
	if (cameras.find(camera_name) == cameras.end()) {
        if (type == cam3D) {
            cameras[camera_name] = new Camera3D();
        } else if (type == cam2D) {
            cameras[camera_name] = new Camera2D();
        } else {
            // TODO: Invalid!
        }
	}
    else
    {
        // TODO: Handle already exists.
    }
    
}

Camera* PT::CameraManager::getCamera(char* camera_name)
{
    if (cameras.find(camera_name) != cameras.end()) {
        return cameras[camera_name];
    } else {
        // TODO: Invalid!
        return nullptr;
    }
}