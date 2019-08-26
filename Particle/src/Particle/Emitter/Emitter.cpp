#include "PCHeader.h"
#include "./Emitter.h"

namespace PT
{
Emitter::Emitter(
    GUILayer *gui,
    std::string name,
    glm::vec4 color,
    float intervalMS,
    glm::vec3 position,
    float force,
    glm::vec2 direction)
    : position(position), color(color), force(force), direction(direction), gui(gui)
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
    Vertex v;
    v.position = glm::vec3(position.x + (direction.x * ((rand() % 50) * force)), position.y + (direction.y * ((rand() % 50) * force)), position.z + (rand() % 100 - 50));
    v.colour = color;
    spawned.push_back(v);
}

std::vector<Vertex> Emitter::update()
{
    std::vector<Vertex> toReturn;

    if (spawned.size() > 0)
    {
        std::copy(spawned.begin(), spawned.end(), std::back_inserter(toReturn));
        spawned.clear();
    }
    return toReturn;
}

void Emitter::GUIElement(std::string name)
{
    ImGui::Begin(name.c_str());
    {
        ImGui::ColorEdit4("Color", &color.r);
        ImGui::SliderFloat("Force", &force, 0.0f, 100.0f, "%.2f");
        ImGui::SliderFloat3("Position", &position.x, -10.0f, 10.0f, "%.2f");
        ImGui::SliderFloat2("Direction", &direction.x, -10.0f, 10.0f, "%.2f");    
    }
    ImGui::End();
}
} // namespace PT
