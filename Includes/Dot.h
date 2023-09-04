#pragma once

#ifndef PONG_DOT_H
#define PONG_DOT_H

#define H_ZOOM_DOT  2
#define W_ZOOM_DOT  2


#include "Entity.h"

class Dot : public Entity
{
    static const int DOT_VEL = 5;

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

    void handleEvent( SDL_Event& e )
    {
        /*//If a key was pressed
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_UP: mVelY -= DOT_VEL; break;
                case SDLK_DOWN: mVelY += DOT_VEL; break;
                case SDLK_LEFT: mVelX -= DOT_VEL; break;
                case SDLK_RIGHT: mVelX += DOT_VEL; break;
            }
        }
            //If a key was released
        else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_UP: mVelY += DOT_VEL; break;
                case SDLK_DOWN: mVelY -= DOT_VEL; break;
                case SDLK_LEFT: mVelX += DOT_VEL; break;
                case SDLK_RIGHT: mVelX -= DOT_VEL; break;
            }
        }
        */
    }

    void update(float deltaTime)
    {
        Entity::update();
        move(deltaTime);

    }

    void move(float deltaTime)
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

private:
    float mVelX = 0;
    float mVelY = 0;
};

#endif //PONG_DOT_H
