#pragma once

#ifndef PONG_DOT_H
#define PONG_DOT_H

#define H_ZOOM_DOT  2
#define W_ZOOM_DOT  2


#include "Entity.h"

class Dot : public Entity
{
    static const int DOT_VEL = 7;

public:
    Dot(float x, float y, SDL_Texture * tex) : Entity(x, y, tex)
    {
        currentFrame.w = 32;
        currentFrame.h = 32;
        collider.h = 32 * H_ZOOM_DOT;
        collider.w = 32 * W_ZOOM_DOT;

        mVelX = DOT_VEL;
        mVelY = DOT_VEL;
    }

    void update() override
    {
        Entity::update();
        move();

    }

    void move()
    {
        if(x > SCREEN_WIDTH - currentFrame.w * W_ZOOM_DOT)
        {
            collisionState = CollisionState::LEFT;
            onCollision(collisionState);
        }
        if(x < 0)
        {
            collisionState = CollisionState::RIGHT;
            onCollision(collisionState);
        }
        if( y < 0 )
        {
            collisionState = CollisionState::DOWN;
            onCollision(collisionState);
        }
        if( y + currentFrame.h * H_ZOOM_DOT > SCREEN_HEIGHT )
        {
            collisionState = CollisionState::UP;
            onCollision(collisionState);
        }

        // Move the dot up and down
        y += mVelY;
        x += mVelX;
    }

    void onCollision(CollisionState& state) override
    {
        /*
         * The state is according to collided object
         * not the collider one.
         * */
        switch(state)
        {
            case CollisionState::UP:
                mVelY = -DOT_VEL;

                break;
            case CollisionState::DOWN:
                mVelY =  DOT_VEL;
                break;
            case CollisionState::LEFT:
                mVelX = -DOT_VEL;
                break;
            case CollisionState::RIGHT:
                mVelX =  DOT_VEL;
                break;
        }

    }

    void onCollisionEnter(CollisionState &state) override
    {
        switch(state)
        {
            case CollisionState::UP:
                mVelY = -DOT_VEL;
                break;
            case CollisionState::DOWN:
                mVelY =  DOT_VEL;
                break;
            case CollisionState::LEFT:
                mVelX = -DOT_VEL;
                break;
            case CollisionState::RIGHT:
                mVelX =  DOT_VEL;
                break;
        }

    }


private:
    float mVelX = 0;
    float mVelY = 0;
};

#endif //PONG_DOT_H
