#include <glm/vec3.hpp>

class SquareRender
{
private:
    unsigned int VAO;

public:
    SquareRender();

    void draw(glm::vec3 color, unsigned int shaderID);
};