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

//        void handle_input(CAM_INPUT_MAP action) override
//        {
//            switch(action)
//            {
//                case LEFT:      // SECTION:: LEFT (-X)
//                    subtractPosition(glm::normalize(glm::cross(getFront(), getUp())) * cSpeed);
//                    break;
//                case RIGHT:     // SECTION: RIGHT (+X)
//                    addPosition(glm::normalize(glm::cross(getFront(), getUp())) * cSpeed);
//                    break;
//                case UP:        // SECTION: UP (-Y)
//                    addPosition(getUp() * cSpeed);
//                    break;
//                case DOWN:      // SECTION: BACKWARD (+Y)
//                    addPosition(getUp() * -cSpeed);
//                    break;
//                default:
//                    std::string r;
//                    switch (action) {
//                        #define CAM_INPUT_DEF(x, y) case y: r = #x; break;
//                        #include CAM_INPUT_DEF_FILE
//                        #undef CAM_INPUT_DEF
//                    }
//                    CORE_LOG_WARN("Camera3D -> Unimplemented input action [{}]", r);
//                    break;
//            }
//        }

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
			  CORE_LOG_WARN("Camera3D -> Unimplemented input action [{}]", r);
			  break;
		  }
		}
    };

}

#endif /* CAMERA3D_HPP */
