#include "ParticleSystem.h"
#include <algorithm>
#include <random>


float randomFloat(float min, float max) {
    // Copy and pasted from chatgpt.

    static std::random_device rd;  // Seed source
    static std::mt19937 gen(rd()); // Mersenne Twister PRNG
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

ParticleSystem::ParticleSystem()
{
}

void ParticleSystem::createParticle(glm::vec3 pos, glm::vec3 vel)
{
    Particle p;
    p.pos = pos;
    p.vel = vel;

    p.pos += glm::vec3(0.0f, randomFloat(-1.5, 1.5), randomFloat(-1.5, 1.5));

    const float PARTICLE_LIFETIME_SEC = 1.0;
    p.life = PARTICLE_LIFETIME_SEC;

    p.vel.x += randomFloat(-0.1, 0);
    p.vel.y += randomFloat(-0.1, 0.1);
    p.vel.z += randomFloat(-0.1, 0.1);

    particles.push_back(p);

    /**
     * I want random x,y,z, but y will mostly be equal to p.y (just slighlty off)
     * 
     * Z_RANGE = [0.5, -0.5]
     * Y_RANGE = pos.y + [0.5, -0.5]
     * X_RANGE = [0.5,-0.5]
     * 
     * random() % RANGE + MIN
     */
}

void ParticleSystem::update(float dt)
{
    const float GRAVITY = 0.1f;

    // remove dead particles
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle& p) { return p.life <= 0; }), particles.end());

    for (auto& p : particles)
    {
        p.pos += p.vel;
        p.vel.y -= GRAVITY * dt;
        p.life -= dt;
    }
}

/**
 * How to remove particles?
 * How to add new particles?
 * 
 * generate like 2 particles every 0.05 seconds?
 * 
 * Give particals a life time. Have a set number or not of particals. 
 * Like 100 max particles.
 */