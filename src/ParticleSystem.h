#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <vector>


struct Particle
{
    glm::vec3 pos = glm::vec3(0.0f);
    glm::vec3 vel = glm::vec3(0.0f);
    glm::vec3 size = glm::vec3(0.5f);
    glm::vec4 color = glm::vec4(1.0f);
    float life = 0.0f;
};

class ParticleSystem
{
public:
    std::vector<Particle> particles;

    ParticleSystem();
    void createParticle(glm::vec3 pos, glm::vec3 vel);
    void update(float dt);
};