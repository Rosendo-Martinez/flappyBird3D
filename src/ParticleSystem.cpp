#include "ParticleSystem.h"
#include <algorithm>
#include <random>

const float PARTICLE_LIFETIME_SEC = 1.0;

float randomFloat(float min, float max) {
    // Copied and pasted from chatgpt.

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
    p.life = PARTICLE_LIFETIME_SEC;

    // random position offset
    p.pos += glm::vec3(0.0f, randomFloat(-1.5, 1.5), randomFloat(-1.5, 1.5));

    // random velocity offset
    p.vel.x += randomFloat(-20.0, -10.0);
    p.vel.y += randomFloat(-4.0, 4.0);
    p.vel.z += randomFloat(-7.0, 7.0);

    // random grey scale color, and random opacity
    p.color = glm::vec4(glm::vec3(randomFloat(0.7f, 1.0f)), 1.0f);

    particles.push_back(p);
}

void ParticleSystem::update(float dt)
{
    // particles float up
    const float GRAVITY = 2.0f;

    // remove dead particles
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle& p) { return p.life <= 0; }), particles.end());

    // update particles
    for (auto& p : particles)
    {
        p.pos += p.vel * dt;
        p.vel.y += GRAVITY * dt;
        p.life -= dt;
        p.color.w = p.life / PARTICLE_LIFETIME_SEC;
    }
}
