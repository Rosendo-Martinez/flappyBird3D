#include <glm/vec3.hpp>
#include <vector>

class FlappyBird
{
public:
    glm::vec3 position;
    glm::vec3 velocity;

    FlappyBird();

    void move(float dt, bool flap = false);
};

struct Map
{
    float left, right, top, bottom;
};

struct Pipe
{
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 velocity;
};

class PipeList
{
public:
    std::vector<Pipe> pipes;
    Map map;

    PipeList(Map map);

    void update(float dt);
};