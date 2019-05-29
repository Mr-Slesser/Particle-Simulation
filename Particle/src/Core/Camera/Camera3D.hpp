#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#include "Camera.h"

namespace PT
{
    class Camera3D : public Camera
    {
    private:
        
    public:
        Camera3D() : Camera(PROJECTION_TYPE::PERSPECTIVE) {}
        ~Camera3D() {}

        void handle_input(CAM_INPUT_MAP action) override
        {
            switch(action)
            {
                case ZOOM_IN:   // SECTION: ZOOM IN (-Z)
                    addPosition(cSpeed * getFront());
                    break;
                case ZOOM_OUT:  // SECTION: ZOOM OUT (+Z)
                    subtractPosition(cSpeed * getFront());
                    break;
                case LEFT:      // SECTION:: LEFT (-X)
                    subtractPosition(glm::normalize(glm::cross(getFront(), getUp())) * cSpeed);
                    break;
                case RIGHT:     // SECTION: RIGHT (+X)
                    addPosition(glm::normalize(glm::cross(getFront(), getUp())) * cSpeed);
                    break;
                case UP:        // SECTION: RIGHT (+X)
                    addPosition(getUp() * cSpeed);
                    break;
                case DOWN:      // SECTION: DOWN (-Y)
                    addPosition(getUp() * -cSpeed);
                    break;
                default:
                    std::string r;
                    switch (action) {
                        #define CAM_INPUT_DEF(x, y) case y: r = #x; break;
                        #include CAM_INPUT_DEF_FILE
                        #undef CAM_INPUT_DEF
                    }
                    CORE_LOG_WARN("Camera3D -> Unimplemented input action [{}]", r);
                    break;
            }
        }
    };

}

#endif /* CAMERA3D_HPP */
