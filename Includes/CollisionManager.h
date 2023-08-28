#pragma once

#ifndef PONG_COLLISIONMANAGER_H
#define PONG_COLLISIONMANAGER_H

#include "Entity.h"
#include <vector>

enum class CollisionState {
    NONE,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class CollisionManager
{
public:

    void Register(Entity& entity)
    {
        entities.push_back(&entity);
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
                    ent1->onCollision();
                    ent2->onCollision();
                }
            }
        }
    }

private:
    std::vector<Entity*> entities;
    CollisionState state = CollisionState::NONE;

    bool checkCollision(CollisionState& state, SDL_Rect& rect1, SDL_Rect& rect2)
    {
        SDL_Rect result;
        bool collision = true;

        if (SDL_IntersectRect(&rect1, &rect2, &result)) {
            // Vérifiez les collisions en fonction des côtés du rectangle.

            int dx = result.x - (rect1.x + rect1.w / 2);
            int dy = result.y - (rect1.y + rect1.h / 2);

            int width = rect1.w / 2 + rect2.w / 2;
            int height = rect1.h / 2 + rect2.h / 2;

            if (std::abs(dx) <= width && std::abs(dy) <= height) {
                if (std::abs(dx) > std::abs(dy)) {
                    if (dx > 0) {
                        state = CollisionState::RIGHT;
                    }
                    else {
                        state = CollisionState::LEFT;
                    }
                }
                else {
                    if (dy > 0) {
                        state = CollisionState::DOWN;
                    }
                    else {
                        state = CollisionState::UP;
                    }
                }
            }
        }
        else {
            state = CollisionState::NONE;
            collision = false;
        }
        return collision;
    }


};

#endif //PONG_COLLISIONMANAGER_H
