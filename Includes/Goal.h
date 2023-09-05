#pragma once
#ifndef PONG_GOAL_H
#define PONG_GOAL_H

#include "Entity.h"
#include "ScoreManager.h"

#define LEFTGOAL true
#define RIGHTGOAL false

class Goal : public Entity
{
public:
    Goal(float p_x, float p_y, bool side, ScoreManager& scoreManager) : Entity(p_x, p_y, nullptr), goalSide(side), score(&scoreManager)
    {
        currentFrame = {(int)x, (int)y, 50, SCREEN_HEIGHT};
        collider = currentFrame;
    }

    void onCollisionEnter(CollisionState &state) override
    {
        if(goalSide == LEFTGOAL)
        {
            score->incrementPlayer2Score();
        }

        if(goalSide == RIGHTGOAL)
        {
            score->incrementPlayer1Score();
        }
    }

private:
    bool goalSide;
    ScoreManager* score;
};

#endif //PONG_GOAL_H
