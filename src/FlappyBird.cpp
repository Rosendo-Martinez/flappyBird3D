#include "FlappyBird.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

FlappyBird::FlappyBird() 
    : position(0.0f), velocity(0.0f)
{
}


void FlappyBird::move(float dt, bool flap)
{
    const float FLAP_SPEED = 60.0f;
    const float GRAVITY = 30.0f;

    if (flap)
    {
        this->position += this->velocity * dt * glm::vec3(0.0, 1.0, 0.0);
        this->velocity += FLAP_SPEED * dt * glm::vec3(0.0,1.0,0.0);
    }
    else
    {
        this->position += this->velocity * dt;
        this->velocity += -GRAVITY * dt * glm::vec3(0.0, 1.0, 0.0);
    }
}

PipeList::PipeList(Map map, GameConfiguration config)
    : map(map), config(config)
{
    lastPipesTime = config.PIPE_GENERATION_RATE;
}

void PipeList::update(float dt)
{
    // check if pipe is 'dead'

    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe & p) { return p.isDead; }), pipes.end());
    for (auto& pipe : pipes)
    {
        pipe.position += pipe.velocity * dt;

        if (pipe.position.x < map.left)
        {
            pipe.isDead = true;
        }
    }

    // make new pipes

    lastPipesTime += dt;
    if (lastPipesTime >= config.PIPE_GENERATION_RATE) // can make pipe?
    {
        lastPipesTime = 0;

        if (rand() % 101 / 100.f <= config.PROBABILITY_OF_TALL_PIPE) // 1 tall pipe
        {
            // const float isTopPipe = rand() % 101 / 100.f <= 0.5f;

            Pipe tall;
            tall.size = glm::vec3(config.PIPE_SIZE_X, (map.top - map.bottom - config.SPACE_BETWEEN_PIPES), config.PIPE_SIZE_Z);
            tall.velocity = glm::vec3(-config.PIPE_SPEED, 0.0f, 0.0f);

            if (isNextTallPipeTop) // top
            {
                tall.position = glm::vec3(map.right, map.top - (tall.size.y/2.0f) , 0.0f);
            }
            else // bottom
            {
                tall.position = glm::vec3(map.right, map.bottom + (tall.size.y/2.0f), 0.0f);
            }

            isNextTallPipeTop = !isNextTallPipeTop;
            pipes.push_back(tall);
        }
        else // 2 regular pipes
        {
            int RANGE_HEIGHT = config.MAX_PIPE_HEIGHT - config.MIN_PIPE_HEIGHT + 1;
            int RANDOM_HEIGHT = rand() %  RANGE_HEIGHT + config.MIN_PIPE_HEIGHT;
            float HEIGHT_BOTTOM = (float) RANDOM_HEIGHT;
            
            Pipe bottom;
            bottom.size = glm::vec3(config.PIPE_SIZE_X, HEIGHT_BOTTOM, config.PIPE_SIZE_Z);
            bottom.position = glm::vec3(map.right, map.bottom + HEIGHT_BOTTOM/2.0f, 0.0f);
            bottom.velocity = glm::vec3(-config.PIPE_SPEED, 0.0f, 0.0f);
            pipes.push_back(bottom);    

            Pipe top;
            top.size = glm::vec3(config.PIPE_SIZE_X, (map.top - map.bottom) - config.SPACE_BETWEEN_PIPES - HEIGHT_BOTTOM, config.PIPE_SIZE_Z);
            top.position = glm::vec3(map.right, map.top - top.size.y/2.0f, 0.0f);
            top.velocity = glm::vec3(-config.PIPE_SPEED, 0.0f, 0.0f);
            pipes.push_back(top);
        }
    }
}

bool isCollision(Pipe p, FlappyBird bird)
{

    glm::vec3 pMax = p.position + p.size/2.0f;
    glm::vec3 pMin = p.position - p.size/2.0f;
    glm::vec3 bMax = bird.position + bird.size/2.0f;
    glm::vec3 bMin = bird.position - bird.size/2.0f;

    // CREDIT: Miguel Casillas
    // Copied and pasted from his tutorial!
    return(pMax.x > bMin.x &&
    pMin.x < bMax.x &&
    pMax.y > bMin.y &&
    pMin.y < bMax.y &&
    pMax.z > bMin.z &&
    pMin.z < bMax.z);
}

bool PipeList::isBirdDead(FlappyBird bird)
{
    for (auto& pipe : pipes)
    {
        if (isCollision(pipe, bird))
        {
            return true;
        }
    }

    return false;
}