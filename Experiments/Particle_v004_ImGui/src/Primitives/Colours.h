#ifndef COLOURS_H
#define COLOURS_H

#include <glm/glm.hpp>

namespace Colour
{
    static const glm::vec4& WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    static const glm::vec4& BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    static const glm::vec4& RED = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    static const glm::vec4& GREEN = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    static const glm::vec4& BLUE = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    static const glm::vec4& GREY = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    static const glm::vec4& PINK = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

} // namespace Colour

#endif /* COLOURS_H */
