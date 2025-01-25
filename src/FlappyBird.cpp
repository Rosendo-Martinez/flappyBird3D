#include "FlappyBird.h"

FlappyBird::FlappyBird() 
    : position(0.0f), velocity(0.0f)
{
}


void FlappyBird::move(float dt, bool flap)
{
    const float FLAP_SPEED = 6.0f;
    const float GRAVITY = 3.0f;

    if (flap)
    {
        this->position += FLAP_SPEED * dt * glm::vec3(0.0, 1.0, 0.0);
        this->velocity *= 0;
    }
    else
    {
        this->position += this->velocity * dt;
        this->velocity += -GRAVITY * dt * glm::vec3(0.0, 1.0, 0.0);
    }
}