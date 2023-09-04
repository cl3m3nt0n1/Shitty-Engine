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

    void Register(Entity& entity)
    {
        entities.push_back(&entity);
    }

    void checkCollisions() {

        CollisionState localState;

        // Collision Detection
        for (int i = 0; i < entities.size(); i++) {
            Entity* ent1 = entities.at(i);
            for (int j = i + 1; j < entities.size(); j++) {
                Entity* ent2 = entities.at(j);

                if (checkCollision(collisionState, *ent1->getCollider(), *ent2->getCollider())) {
                    // Push the colliding pair into the collisionPairs vector
                    collisionPairs.emplace_back(ent1, ent2);
                    localState = collisionState;
                }
            }
        }

        // Collision resolution
        for (const auto& pair : collisionPairs) {
            Entity* ent1 = pair.first;
            Entity* ent2 = pair.second;

            if (!ent1->getIsColliding()) {
                ent1->setIsColliding(true);
                ent1->onCollisionEnter(localState);
            }

            if (!ent2->getIsColliding()) {
                ent2->setIsColliding(true);
                ent2->onCollisionEnter(localState);
            }
        }

        // End of collision detection
        for (Entity* ent : entities) {
            if (ent->getIsColliding()) {
                bool stillColliding = false;
                for (const auto& pair : collisionPairs) {
                    if (pair.first == ent || pair.second == ent) {
                        stillColliding = true;
                        break;
                    }
                }
                if (!stillColliding) {
                    ent->setIsColliding(false);
                    ent->onCollisionExit(localState);
                }
            }
        }
        collisionPairs.clear();
        localState = CollisionState::NONE;
        collisionState = CollisionState::NONE;
    }


private:
    std::vector<Entity*> entities;
    std::vector<std::pair<Entity*, Entity*>> collisionPairs;
    CollisionState collisionState;

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

};

#endif //PONG_COLLISIONMANAGER_H
