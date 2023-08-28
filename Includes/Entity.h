#pragma once

#ifndef PONG_ENTITY_H
#define PONG_ENTITY_H

#include <SDL2/SDL.h>
#include <iostream>

class Entity{
public:

    Entity(float p_x, float p_y, SDL_Texture* tex) : x(p_x), y(p_y), texture(tex)
    {

        currentFrame = {0,0,32,32};
        collider = currentFrame;
    }

    float getX() { return x; }
    float getY() { return y; }
    void setX(float p_x) {x = p_x; }
    void setY(float p_y) {y = p_y; }

    SDL_Rect* getCollider() { return &collider; };
    SDL_Texture* getTex() { return texture; }
    SDL_Rect getCurrentFrame() { return currentFrame ; }

    void update()
    {
        collider.x = x;
        collider.y = y;
    }

    virtual void onCollision()
    {
        std::cout << "ENTITY : Collision Detected !" << std::endl;
    }


protected:

    SDL_Rect currentFrame;
    SDL_Texture* texture = NULL;
    float x = 0, y = 0;
    SDL_Rect collider;

};

#endif //PONG_ENTITY_H
