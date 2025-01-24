#include "FlappyBird.h"

FlappyBird::FlappyBird() 
    : position(0.0f), velocity(0.0f)
{
}


void FlappyBird::move(float dt, bool flap)
{
    /**
     * Super simple logic for moving.
     * 
     * if flap:
     *   cur_pos += flap_speed * dt
     * 
     * pos_next += vel_cur * dt
     * vel_next += grav * dt
     *   
     */

    const float FLAP_SPEED = 1.0f;
    const float GRAVITY = 0.09f;

    if (flap)
    {
        this->position += FLAP_SPEED * dt * glm::vec3(0.0, 1.0, 0.0);
    }
    else
    {
        this->position += this->velocity * dt;
        this->velocity += -GRAVITY * dt * glm::vec3(0.0, 1.0, 0.0);
    }
}