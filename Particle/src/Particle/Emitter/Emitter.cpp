#include "PCHeader.h"
#include "./Emitter.h"

namespace PT
{
Emitter::Emitter(
    GL::Datastore *_datastore,
    GUILayer *gui,
    std::string name,
    glm::vec4 color,
    float intervalMS,
    glm::vec3 position,
    float force,
    glm::vec3 direction)
    : datastore(_datastore), position(position), color(color), force(force), direction(glm::normalize(direction)), gui(gui), enabled(true)
{
    timer.setInterval([this]() { this->spawnParticle(); }, intervalMS);
    gui->addElement([this, name]() {
        this->GUIElement(name);
    });
}

Emitter::~Emitter()
{
    timer.end();
}

void Emitter::spawnParticle()
{
  if (enabled)
  {
    ParticleData v;
    v.position = glm::vec3(position.x, position.y, position.z);
    v.velocity = glm::vec3(direction.x * force, direction.y * force, direction.z * force);

    v.colour = color;
    v.lifespan = 1.0f;
    v.mass = 1.0f;

    datastore->addToQueue(v);
  }
}

void Emitter::update(GL::DebugDatastore *debugdatastore)
{
//  if (enabled)
//  {
//    debugdatastore->addElement({position, Colour::RED});
//    auto secondVertexPosition = glm::vec3(
//        position.x + (direction.x * force),
//        position.y + (direction.y * force),
//        position.z + (direction.z * force));
//    debugdatastore->addElement({secondVertexPosition, Colour::RED});
//  }
}

void Emitter::GUIElement(std::string name)
{
    ImGui::Begin(name.c_str());
    {
      	ImGui::Checkbox("Enabled", &enabled);
        ImGui::ColorEdit4("Color", &color.r);
        ImGui::DragFloat("Force", &force, 0.1f, 0.0f, 1.0f, "%.2f");
        ImGui::DragFloat3("Position", &position.x, 1.0f, 0.0f, 500.0f, "%.2f");
        ImGui::DragFloat3("Direction", &direction.x, 0.1f, -1.0f, 1.0f, "%.2f");
    }
    ImGui::End();
}
} // namespace PT
