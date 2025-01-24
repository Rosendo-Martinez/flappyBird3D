#include <glm/vec3.hpp>

class FlappyBird
{
public:
    glm::vec3 position;
    glm::vec3 velocity;

    FlappyBird();

    void move(float dt, bool flap = false);
};