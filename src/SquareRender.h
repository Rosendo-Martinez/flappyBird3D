#include <glm/vec3.hpp>
#include "Shader.h"

class SquareRender
{
private:
    unsigned int VAO;
    Shader shader;

public:
    SquareRender(Shader shader);

    void draw(glm::vec3 color);
};