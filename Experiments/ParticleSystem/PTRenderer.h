#ifndef PTRENDERER_H
#define PTRENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Particle.h"
#include "UpdateProgram.h"
#include "RenderProgram.h"

#include "Texture.h"
#include "RandomTexture.hpp"

#define PT_RENDERER_MAX_PARTICLES 500
#define ZERO_MEM(a) memset(a, 0, sizeof(a))

namespace PT
{
    class PTRenderer
    {
    private:
        UpdateProgram* update_program;
        RenderProgram* render_program;

        unsigned int buffer_feedback[2];
        unsigned int current_BF = 0;
        unsigned int buffer_particle[2];
        unsigned int current_BP = 0;

        bool first = true;

        int time_ellapsed = 0;

        RandomTexture m_randomTexture;
        Texture* texture;
        
    public:
        PTRenderer();
        virtual ~PTRenderer();

        void init();

        void clear() const;
        void draw(float &dt);

        void update(int &dt);
        void render(float &dt);
    };
} // PT

#endif /* PTRENDERER_H */
