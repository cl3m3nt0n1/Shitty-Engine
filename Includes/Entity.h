#pragma once

#ifndef PONG_ENTITY_H
#define PONG_ENTITY_H

#include <SDL2/SDL.h>
#include "utils.h"
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Entity{
public:

    Entity(float p_x, float p_y, SDL_Texture* tex) : x(p_x), y(p_y), texture(tex)
    {

        currentFrame = {0,0,800,600};
        collider = currentFrame;
    }

    float getX() { return x; }

    float getY() { return y; }

    void setX(float p_x) {x = p_x; }

    void setY(float p_y) {y = p_y; }

    bool getIsColliding() const {
        return isColliding;
    }

    void setIsColliding(bool isColliding) {
        this->isColliding = isColliding;
    }

    SDL_Rect* getCollider() { return &collider; };

    SDL_Texture* getTex() { return texture; }

    SDL_Rect getCurrentFrame() { return currentFrame ; }

    virtual void update()
    {
        collider.x = x;
        collider.y = y;

    }

    virtual void onCollision(CollisionState&)
    {
        std::cout << "ENTITY : Collision Detected !" << std::endl;
    }

    virtual void onCollisionEnter()
    {

    }
    virtual void onCollisionExit()
    {

    }


protected:

    SDL_Rect currentFrame;
    SDL_Texture* texture = NULL;
    float x, y;
    SDL_Rect collider;
    bool isColliding = false;

    CollisionState collisionState = CollisionState::NONE;

};

#endif //PONG_ENTITY_H
