#pragma once

#ifndef PONG_COLLISIONMANAGER_H
#define PONG_COLLISIONMANAGER_H

#include "Entity.h"
#include "utils.h"
#include "Dot.h"
#include "Goal.h"
#include "ScoreManager.h"
#include <vector>

class CollisionManager
{
public:

    CollisionManager(ScoreManager& score) : scoreManager(&score)
    {

    }

    void Register(Entity& entity)
    {
        entities.push_back(&entity);
    }

    void RegisterDoatAndGoals(Dot& dot, Goal& leftGoal, Goal& rightGoal)
    {
        dotPointer = &dot;
        leftGoalPointer = &leftGoal;
        rightGoalPointer = &rightGoal;

    }

    void checkCollisions()
    {
        for(int i = 0 ; i < entities.size() ; i++)
        {
            for(int j = i+1 ; j < entities.size() ; j++)
            {
                Entity* ent1 = entities.at(i);
                Entity* ent2 = entities.at(j);

                if(checkCollision(state, *ent2->getCollider(), *ent1->getCollider()))
                {
                    ent1->onCollision(state);
                    ent2->onCollision(state);
                }
            }
        }
    }

    void checkCollisionsDotToGoal()
    {
        if(checkCollisionDotToGoal(dotPointer->getCollider(), leftGoalPointer->getCollider()))
        {
            leftGoalPointer->onCollision(state);
            scoreManager->incrementPlayer2Score();
        }
        if(checkCollisionDotToGoal(dotPointer->getCollider(), rightGoalPointer->getCollider()))
        {
            rightGoalPointer->onCollision(state);
            scoreManager->incrementPlayer1Score();
        }
    }

private:
    std::vector<Entity*> entities;
    Dot* dotPointer;
    Goal* leftGoalPointer;
    Goal* rightGoalPointer;
    ScoreManager* scoreManager;

    CollisionState state = CollisionState::NONE;

    /*
     * Checks collision between two objects.
     * Updates the state pointer according to the result rectangle.
     * The result rectangle is the rectangle that appears when a collision occurs
     * between rect1 and rect2.
     * */
    bool checkCollision(CollisionState& state, SDL_Rect& rect1, SDL_Rect& rect2) {

        SDL_Rect result;

        if (SDL_IntersectRect(&rect1, &rect2, &result)) {

            if (result.y == rect1.y || result.y == rect2.y + rect2.h) {

                (result.y == rect1.y) ? state = CollisionState::UP : state = CollisionState::DOWN;
                return true;
            }
            else if (result.x == rect1.x || result.x == rect2.x + rect2.w) {

                (result.x == rect1.x) ? state = CollisionState::LEFT : state = CollisionState::RIGHT;
                return true;
            }
        }
        else
        {
            state = CollisionState::NONE;
            return false;
        }
    }

    bool checkCollisionDotToGoal(SDL_Rect* dotRect, SDL_Rect* goalRect)
    {
        if(SDL_HasIntersection(dotRect, goalRect) == SDL_TRUE)
            return true;
        else
            return false;

    }
};

#endif //PONG_COLLISIONMANAGER_H
