#include "CameraManager.h"

#include "../Input/InputManager.h"

namespace PT
{
    // SECTION: Private functions
    CameraManager *CameraManager::instance = 0;

    CameraManager *CameraManager::get()
    {
        if (!instance)
            instance = new CameraManager;
        return instance;
    }

    CameraManager::CameraManager()
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

    bool CameraManager::initCameras()
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
    CameraManager::~CameraManager()
    {
        for (auto ele: cameras)
        {
            delete ele.second;
            ele.second = nullptr;
        }

        cameras.clear();
    }

    bool CameraManager::startup()
    {
        if (!initCameras()) {
            CORE_LOG_ERROR("CameraManager::startup() - Failed to initialize cameras.");
            return false;
        }
        
        CORE_LOG_TRACE("Running... register_input_dispatch");
        return true;
    }

    bool CameraManager::registerCamera(const char* camera_name, SM_CAM_TYPE type, const CameraData& data)
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

    Camera* CameraManager::getCamera(const char* camera_name)
    {
        if (cameras.find(camera_name) != cameras.end()) {
            return cameras[camera_name];
        } else {
            CORE_LOG_WARN("CameraManager::getCamera() - Name invalid -> {}", camera_name);
            return nullptr;
        }
    }

    void CameraManager::register_input_dispatch()
    {
        CORE_LOG_INFO("CameraManager::register_input_dispatch() ----------")
        #define CAM_INPUT_DEF(x,y) CORE_LOG_TRACE("    Register -> Action [{}], Key [{}]", #x, #y); \
                    InputManager::get()->register_dispatch(#y, y, this->instance);
        #include CAM_INPUT_DEF_FILE
        #undef CAM_INPUT_DEF
    }

    void CameraManager::receive_dispatched_input(unsigned int key)
    {
        cameras["DEFAULT"]->handle_input(static_cast<CAM_INPUT_MAP>(key));
        // std::string r;
        // switch (key) {
        //     #define CAM_INPUT_DEF(x, y) case y: CORE_LOG_INFO("{}", #x); break;
        //     #include CAM_INPUT_DEF_FILE
        //     #undef CAM_INPUT_DEF
        // }
    }

}

