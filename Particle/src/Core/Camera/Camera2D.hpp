#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include "Camera.h"

namespace PT
{
    class Camera2D : public Camera
    {
    private:
        
    public:
        Camera2D() : Camera(PROJECTION_TYPE::ORTHOGRAPHIC) {}
        ~Camera2D() {}

        void handle_input(CAM_INPUT_MAP action) override
        {
            switch(action)
            {
			  case LEFT:      // SECTION:: LEFT (-X)
				updatePosition(glm::vec3(-1.0f, 0.0f, 0.0f));
				break;
			  case RIGHT:     // SECTION: RIGHT (+X)
				updatePosition(glm::vec3(1.0f, 0.0f, 0.0f));
				break;
			  case UP:        // SECTION: UP (+Z)
				updatePosition(glm::vec3(0.0f, 0.0f, -1.0f));
				break;
			  case DOWN:      // SECTION: DOWN (-Z)
				updatePosition(glm::vec3(0.0f, 0.0f, 1.0f));
				break;
			  case RAISE:
				updatePosition(glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			  case LOWER:
				updatePosition(glm::vec3(0.0f, -1.0f, 0.0f));
				break;
                default:
                    std::string r;
                    switch (action) {
                        #define CAM_INPUT_DEF(x, y) case y: r = #x; break;
                        #include CAM_INPUT_DEF_FILE
                        #undef CAM_INPUT_DEF
                    }
                    CORE_LOG_WARN("Camera2D -> Unimplemented input action [{}]", r);
                    break;
            }
        }
    };
}


#endif /* CAMERA2D_HPP */
