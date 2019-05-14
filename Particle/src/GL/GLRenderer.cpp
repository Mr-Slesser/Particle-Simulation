#include "GLRenderer.h"

GL::GLRenderer::GLRenderer()
{

}

GL::GLRenderer::~GLRenderer()
{

}

void GL::GLRenderer::init(unsigned int indices[6], Vertex v[4], int vsize) 
{
    program = new GLSLProgram();
    vao = new VAO();
    //vb = new GL::VertexBuffer(vertices, 4 * 3 * sizeof(float), GL_STATIC_DRAW);
    vbo = new VBO(v, vsize, GL_STATIC_DRAW);

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3);
    vbl.push<float>(4);

    vao->addBuffer(*vbo, vbl);
    ebo = new EBO(indices, 6, GL_STATIC_DRAW);
}

void GL::GLRenderer::clear() const
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GL::GLRenderer::draw(float& dt, Camera* cam) const
{
    program->use();
    program->setFloat("time", dt);

    // REVIEW: Model Matrix
        // This is set per model / Object.
        // I.e loop through
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    //model = glm::rotate(model, (dt) * glm::radians(90.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    int modelLoc = glGetUniformLocation(program->getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // REVIEW: View Matrix
        // Set once
    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    float r = 10.0f;
    //float cX = sin(glfwGetTime()) * r;
    float cY = cos(glfwGetTime()) * r;
    //float cZ = cos(glfwGetTime()) * r;
    float cX = 0.0f;
    float cZ = 3.0f;
    //glm::mat4 view = cam->setLookAt(cX, cY, cZ);
    glm::mat4 view = cam->getLookAt();
    int viewLoc = glGetUniformLocation(program->getID(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    // REVIEW: Projection Matrix
        // Generate Once! (Well, on resize)
        // Set once.
    glm::mat4 projection;
    projection = cam->getProjection();
    int projectionLoc = glGetUniformLocation(program->getID(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    vao->bind();
    ebo->bind();
    glDrawElements(GL_TRIANGLES, ebo->getCount(), GL_UNSIGNED_INT, nullptr);
}