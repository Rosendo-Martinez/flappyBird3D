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
    lastPipesTime = 4.0f; // PIPES GEN RATE
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

    const float PIPES_GEN_RATE = 4.0f;
    lastPipesTime += dt;

    if (lastPipesTime >= PIPES_GEN_RATE)
    {
        lastPipesTime = 0;

        const float PROBABILITY_OF_TALL_PIPE = 0.25f;

        const float PIPE_WIDTH = 10.0f;
        const float PIPE_LENGTH = 10.0f;
        const float SPEED_X = -(map.right - map.left) / 6.5f;
        const float SPACE_BETWEEN = config.SPACE_BETWEEN_PIPES;

        if (rand() % 101 / 100.f <= PROBABILITY_OF_TALL_PIPE)
        {
            const float isTopPipe = rand() % 101 / 100.f <= 0.5f;

            Pipe tall;
            tall.size = glm::vec3(PIPE_WIDTH, (map.top - map.bottom - SPACE_BETWEEN), PIPE_LENGTH);
            tall.velocity = glm::vec3(SPEED_X, 0.0f, 0.0f);

            if (isTopPipe)
            {
                tall.position = glm::vec3(map.right, map.top - (tall.size.y/2.0f) , 0.0f);
            }
            else
            {
                tall.position = glm::vec3(map.right, map.bottom + (tall.size.y/2.0f), 0.0f);
            }

            pipes.push_back(tall);
        }
        else 
        {
            // make new pipes
            // create two pipes
            float HEIGHT_BOTTOM = (map.top - map.bottom) * 0.5 - SPACE_BETWEEN * 0.5 + map.bottom;



            int RANGE_HEIGHT = config.MAX_PIPE_HEIGHT - config.MIN_PIPE_HEIGHT + 1;
            int RANDOM_HEIGHT = rand() %  RANGE_HEIGHT + config.MIN_PIPE_HEIGHT;

            HEIGHT_BOTTOM = (float) RANDOM_HEIGHT;
            
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
    }
}

bool isCollision(Pipe p, FlappyBird bird)
{

    glm::vec3 pMax = p.position + p.size/2.0f;
    glm::vec3 pMin = p.position - p.size/2.0f;

    glm::vec3 bMax = bird.position + bird.size/2.0f;
    glm::vec3 bMin = bird.position - bird.size/2.0f;

    // CREDIT: Miguel Casillas
    // Copyied and pasted from his tutorial!
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