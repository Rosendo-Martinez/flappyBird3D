#include "ParticleSystem.h"
#include <algorithm>

ParticleSystem::ParticleSystem()
{
}

void ParticleSystem::createParticle(glm::vec3 pos, glm::vec3 vel)
{
    Particle p;
    p.pos = pos;
    p.vel = vel;

    const float PARTICLE_LIFETIME_SEC = 1.5;
    p.life = PARTICLE_LIFETIME_SEC;

    particles.push_back(p);
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