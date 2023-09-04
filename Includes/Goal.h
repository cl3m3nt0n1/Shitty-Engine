#pragma once
#ifndef PONG_GOAL_H
#define PONG_GOAL_H

#include "Entity.h"

class Goal : public Entity
{
public:
    Goal(float p_x, float p_y) : Entity(p_x, p_y, nullptr)
    {
        currentFrame = {(int)x, (int)y, 50, SCREEN_HEIGHT};
        collider = currentFrame;
    }

    void onCollision(CollisionState &state) override {
        std::cout << "Goal : collision detected" << std::endl;
    }

};

#endif //PONG_GOAL_H
