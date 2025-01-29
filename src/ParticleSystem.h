#include <glm/vec3.hpp>
#include <vector>
/**
 * Partical system
 * 
 * spawns the particals
 * updates the particals
 */

struct Particle
{
    glm::vec3 pos = glm::vec3(0.0f);
    glm::vec3 vel = glm::vec3(0.0f);
    glm::vec3 size = glm::vec3(0.5f);
    float life = 0.0f;

    // size? color?
};

class ParticleSystem
{
public:
    std::vector<Particle> particles;

    ParticleSystem();
    void createParticle(glm::vec3 pos, glm::vec3 vel);
    void update(float dt);
};