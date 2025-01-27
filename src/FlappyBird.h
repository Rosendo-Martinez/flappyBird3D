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
    // Pipe configuration
    int SPACE_BETWEEN_PIPES;
    int MIN_PIPE_HEIGHT;
    int MAX_PIPE_HEIGHT;
    float PIPE_SIZE_X;
    float PIPE_SIZE_Z;
    float PIPE_SPEED; // >0
    float PROBABILITY_OF_TALL_PIPE; // [0,1]
    float PIPE_GENERATION_RATE; // seconds
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
    bool isNextTallPipeTop = true;

    PipeList(Map map, GameConfiguration config);

    void update(float dt);
    bool isBirdDead(FlappyBird bird);
};