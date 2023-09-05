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
        // Calcule les intervalles de collision sur l'axe des X
        int rect1Left = rect1.x;
        int rect1Right = rect1.x + rect1.w;
        int rect2Left = rect2.x;
        int rect2Right = rect2.x + rect2.w;

        // Calcule les intervalles de collision sur l'axe des Y
        int rect1Top = rect1.y;
        int rect1Bottom = rect1.y + rect1.h;
        int rect2Top = rect2.y;
        int rect2Bottom = rect2.y + rect2.h;

        // Vérifie s'il y a collision sur l'axe des X
        if (rect1Right <= rect2Left || rect1Left >= rect2Right) {
            return false;
        }

        // Vérifie s'il y a collision sur l'axe des Y
        if (rect1Bottom <= rect2Top || rect1Top >= rect2Bottom) {
            return false;
        }

        // Si collision, détermine le côté de la collision
        state = CollisionState::NONE;
        if (rect1Bottom > rect2Top && rect1Top < rect2Top) {
            state = CollisionState::UP;
        } else if (rect1Top < rect2Bottom && rect1Bottom > rect2Bottom) {
            state = CollisionState::DOWN;
        } else if (rect1Right > rect2Left && rect1Left < rect2Left) {
            state = CollisionState::LEFT;
        } else if (rect1Left < rect2Right && rect1Right > rect2Right) {
            state = CollisionState::RIGHT;
        }

        return true;
    }


};

#endif //PONG_COLLISIONMANAGER_H
