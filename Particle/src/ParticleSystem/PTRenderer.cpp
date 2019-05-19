#include "PTRenderer.h"

PT::PTRenderer::PTRenderer()
{

}

PT::PTRenderer::~PTRenderer()
{

}

// void PT::PTRenderer::init(unsigned int indices[6], Vertex v[4], int vsize) 
void PT::PTRenderer::init() 
{
    update_program = new PTProgram(VS_UPDATE, FS_UPDATE, 2);
    update_program->use();

    model_matrix_loc = glGetUniformLocation(update_program->getID(), "model_matrix");
    projection_matrix_loc = glGetUniformLocation(update_program->getID(), "projection_matrix");
    triangle_count_loc = glGetUniformLocation(update_program->getID(), "triangle_count");
    time_step_loc = glGetUniformLocation(update_program->getID(), "time_step");

    static const char * varyings2[] =
    {
        "world_space_position"
    };

    render_program = new PTProgram(VS_RENDER, FS_RENDER, 1);

    render_program->use();

    render_model_matrix_loc = glGetUniformLocation(render_program->getID(), "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(render_program->getID(), "projection_matrix");

    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);
    
    int i, j;
    for (i = 0; i < 2; i++)
    {
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, vbo[i]);
        glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, PTRENDERER_MAX_POINTS * (sizeof(glm::vec4) + sizeof(glm::vec3)), NULL, GL_DYNAMIC_COPY);
        if (i == 0)
        {
            struct buffer_t {
                glm::vec4 position;
                glm::vec3 velocity;
            } * buffer = (buffer_t *)glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_WRITE_ONLY);

            for (j = 0; j < PTRENDERER_MAX_POINTS; j++)
            {
                buffer[j].velocity = glm::vec3((rand() % 100) / 100, (rand() % 100) / 100, (rand() % 100) / 100);
                buffer[j].position = glm::vec4(buffer[j].velocity + glm::vec3(-0.5f, 40.0f, 0.0f), 1.0f);
                buffer[j].velocity = glm::vec3(buffer[j].velocity[0], buffer[j].velocity[1] * 0.3f, buffer[j].velocity[2] * 0.3f);
            }

            glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);
        }

        glBindVertexArray(vao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) + sizeof(glm::vec3), NULL);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) + sizeof(glm::vec3), (GLvoid *)sizeof(glm::vec4));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

    }

    glGenBuffers(1, &geometry_vbo);
    glGenTextures(1, &geometry_tex);
    glBindBuffer(GL_TEXTURE_BUFFER, geometry_vbo);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_COPY);
    glBindTexture(GL_TEXTURE_BUFFER, geometry_tex);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, geometry_vbo);

    glGenVertexArrays(1, &render_vao);
    glBindVertexArray(render_vao);
    glBindBuffer(GL_ARRAY_BUFFER, geometry_vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);


}

void PT::PTRenderer::viewMatrix(float& dt, Camera* cam)
{
    //view = cam->getLookAt();
    //int viewLoc = glGetUniformLocation(program->getID(), "view");
    //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void PT::PTRenderer::projectionMatrix(float& dt, Camera* cam)
{
    //projection = cam->getProjection();
    //int projectionLoc = glGetUniformLocation(program->getID(), "projection");
    //glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void PT::PTRenderer::clear() const
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PT::PTRenderer::draw(float& dt, Camera* cam)
{
    static int frame_count = 0;
    float t = frame_count / 10000;
    static float q = 0.0f;
    static const glm::vec3 X(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z(0.0f, 0.0f, 1.0f);

    glm::mat4 projection_matrix = cam->getProjection() * cam->getLookAt();
    glm::mat4 model_matrix = glm::mat4(1.0f);
    //(glm::scale(0.3f) *
      //                       glm::rotate(t * 360.0f, 0.0f, 1.0f, 0.0f) *
        //                     glm::rotate(t * 360.0f * 3.0f, 0.0f, 0.0f, 1.0f));

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    render_program->use();
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, value_ptr(model_matrix));
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, value_ptr(projection_matrix));

    glBindVertexArray(render_vao);

    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, geometry_vbo);

    glBeginTransformFeedback(GL_TRIANGLES);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glEndTransformFeedback();

    update_program->use();
    model_matrix = glm::mat4(1.0f);
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, value_ptr(model_matrix));
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, value_ptr(projection_matrix));
    glUniform1i(triangle_count_loc, PTRENDERER_MAX_POINTS);

    if (t > q)
    {
        glUniform1f(time_step_loc, (t - q) * 2000.0f);
    }

    q = t;

    if ((frame_count & 1) != 0)
    {
        glBindVertexArray(vao[1]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[0]);
    }
    else
    {
        glBindVertexArray(vao[0]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[1]);
    }

    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, std::min(PTRENDERER_MAX_POINTS, (frame_count >> 3)));
    glEndTransformFeedback();

    glBindVertexArray(0);

    frame_count++;
}