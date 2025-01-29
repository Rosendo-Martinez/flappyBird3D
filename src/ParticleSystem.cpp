#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

void ParticleSystem::createParticle(glm::vec3 pos, glm::vec3 vel)
{
    Particle p;
    p.pos = pos;
    p.vel = vel;

    particles.push_back(p);
}

void ParticleSystem::update(float dt)
{
    const float GRAVITY = 0.1f;

    for (auto& p : particles)
    {
        p.pos += p.vel;
        p.vel.y -= GRAVITY * dt;
    }
}