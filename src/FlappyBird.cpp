#include "FlappyBird.h"
#include <algorithm>

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

PipeList::PipeList(Map map)
    : map(map)
{
    // create two pipes
    const float SPEED_X = -(map.right - map.left) / 13.0f;
    const float SPACE_BETWEEN = (map.top - map.bottom) * 0.25 + map.bottom;
    const float HEIGHT_BOTTOM = (map.top - map.bottom) * 0.5 - SPACE_BETWEEN * 0.5 + map.bottom;

    const float PIPE_WIDTH = 10.0f;
    const float PIPE_LENGTH = 10.0f;
    
    Pipe bottom;
    bottom.size = glm::vec3(PIPE_WIDTH, HEIGHT_BOTTOM, PIPE_LENGTH);
    bottom.position = glm::vec3(map.right, map.bottom + HEIGHT_BOTTOM/2.0f, 0.0f);
    bottom.velocity = glm::vec3(SPEED_X, 0.0f, 0.0f);

    Pipe top;
    top.size = glm::vec3(PIPE_WIDTH, (map.top - map.bottom) - SPACE_BETWEEN - HEIGHT_BOTTOM, PIPE_LENGTH);
    top.position = glm::vec3(map.right, map.top - top.size.y/2.0f, 0.0f);
    top.velocity = glm::vec3(SPEED_X, 0.0f, 0.0f);

    pipes.push_back(top);
    pipes.push_back(bottom);    
}

void PipeList::update(float dt)
{
    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe & p) { return p.isDead; }), pipes.end());

    for (auto& pipe : pipes)
    {
        pipe.position += pipe.velocity * dt;

        if (pipe.position.x < map.left)
        {
            pipe.isDead = true;
        }
    }

}