#include "PTRenderer.h"
#include "../Core/Camera/CameraManager.h"

PT::PTRenderer::PTRenderer()
{
    ZERO_MEM(buffer_feedback);
    ZERO_MEM(buffer_particle);
}

PT::PTRenderer::~PTRenderer()
{
    // TODO: Delete the two buffer arrays.
}

void PT::PTRenderer::init() 
{
    Particle Particles[PT_RENDERER_MAX_PARTICLES];
    ZERO_MEM(Particles);

    Particles[0].Type = PARTICLE_TYPE_LAUNCHER;
    Particles[0].Pos = glm::vec3(0.0f, 0.0f, 1.0f);
    Particles[0].Vel = glm::vec3(0.0f, 0.0001f, 0.0f);
    Particles[0].LifetimeMillis = 0.0f;
    
    glGenTransformFeedbacks(2, buffer_feedback);    
    glGenBuffers(2, buffer_particle);

    for (unsigned int i = 0; i < 2 ; i++) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, buffer_feedback[i]);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_particle[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Particles), Particles, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffer_particle[i]);        
    }

    // TODO: Uniforms..
    update_program = new UpdateProgram();
    update_program->setInt("gRandomTexture", 3);
    update_program->setFloat("gLauncherLifetime", 100.0f);
    update_program->setFloat("gShellLifetime", 10000.0f);
    update_program->setFloat("gSecondaryShellLifetime", 2500.0f);

    m_randomTexture.InitRandomTexture(1000);
    m_randomTexture.Bind(GL_TEXTURE3);

    render_program = new RenderProgram();
    render_program->setInt("gColorMap", 0);
    render_program->setFloat("gBillboardSize", 0.01f);
    texture = new Texture(GL_TEXTURE_2D, TEXTURE_LOC);
    texture->Load();
}

void PT::PTRenderer::clear() const
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PT::PTRenderer::draw(float& dt)
{
    int dt_ms = (int)(dt * 1000);
    time_ellapsed += dt_ms;
    update(dt_ms);
    render(dt);

    current_BP = current_BF;
    current_BF = (current_BF + 1) & 0x1;
}

void PT::PTRenderer::update(int &dt)
{
    
    update_program->use();

    update_program->setInt("gTime", time_ellapsed);
    update_program->setInt("gDeltaTimeMillis", dt);

    m_randomTexture.Bind(GL_TEXTURE3);

    glEnable(GL_RASTERIZER_DISCARD);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffer_particle[current_BP]);    
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, buffer_feedback[current_BP]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)16);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)28);
    
    glBeginTransformFeedback(GL_POINTS);

    if (first) {
        glDrawArrays(GL_POINTS, 0, 1);

        first = false;
    }
    else {
        glDrawTransformFeedback(GL_POINTS, buffer_feedback[current_BP]);
    }            
    
    glEndTransformFeedback();

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

void PT::PTRenderer::render(float &dt)
{
    render_program->use();
    render_program->setFloat3("gCameraPos", CameraManager::get()->getCamera()->getPosition());
    render_program->setMat4x4f("gVP", CameraManager::get()->getCamera()->getProjection() * CameraManager::get()->getCamera()->getLookAt());
    texture->Bind(GL_TEXTURE0);

    glDisable(GL_RASTERIZER_DISCARD);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_particle[current_BF]);    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);  // position
    glDrawTransformFeedback(GL_POINTS, buffer_feedback[current_BF]);
    glDisableVertexAttribArray(0);
}