#include <glm/vec3.hpp>
#include <vector>

class FlappyBird
{
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 size;

    FlappyBird();

    void move(float dt, bool flap = false);
};

struct Map
{
    float left, right, top, bottom;
};

struct GameConfiguration
{
    int spaceBetween, minHeight, maxHeight;
};

struct Pipe
{
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 velocity;

    bool isDead = false;
};

class PipeList
{
public:
    std::vector<Pipe> pipes;
    Map map;
    GameConfiguration config;
    float lastPipesTime = 0.0f;

    PipeList(Map map, GameConfiguration config);

    void update(float dt);
    bool isBirdDead(FlappyBird bird);
};