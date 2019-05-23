#include "CameraManager.h"

// SECTION: Private functions
PT::CameraManager *PT::CameraManager::instance = 0;

PT::CameraManager *PT::CameraManager::get()
{
    if (!instance)
        instance = new PT::CameraManager;
    return instance;
}

PT::CameraManager::CameraManager()
{
    // REVIEW: Do we want to actually pass params to this, so make it a separate function?
    if(startup())
    {
        CORE_LOG_TRACE("CameraManager::Constructor - Startup completed.");
    }
    else
    {
        CORE_LOG_ERROR("CameraManager::Constructor - Startup error.");
        assert(false);
    }
}

bool PT::CameraManager::initCameras()
{
    // By default create the default camera!
    if (!registerCamera("DEFAULT", cam3D))
    {
        CORE_LOG_ERROR("CameraManager::initCameras() - Default camera could not be initialized.");
        return false;
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
    if (!initCameras()) {
        CORE_LOG_ERROR("CameraManager::startup() - Failed to initialize cameras.");
        return false;
    }
    
    return true;
}

bool PT::CameraManager::registerCamera(const char* camera_name, SM_CAM_TYPE type, const CameraData& data)
{
    // TODO: Handle data!
	if (cameras.find(camera_name) == cameras.end()) {
        if (type == cam3D) {
            cameras[camera_name] = new Camera3D();
        } else if (type == cam2D) {
            cameras[camera_name] = new Camera2D();
        } else {
            CORE_LOG_WARN("CameraManager::registerCamera() - Invalid type specified -> {}", type);
            return false;
        }
	}
    else
    {
        CORE_LOG_WARN("CameraManager::registerCamera() - Name already exists -> {}", camera_name);
        return false;
    }
    
    return true;
}

Camera* PT::CameraManager::getCamera(const char* camera_name)
{
    if (cameras.find(camera_name) != cameras.end()) {
        return cameras[camera_name];
    } else {
        CORE_LOG_WARN("CameraManager::getCamera() - Name invalid -> {}", camera_name);
        return nullptr;
    }
}