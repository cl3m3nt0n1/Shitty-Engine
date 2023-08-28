#pragma once

#ifndef PONG_DOT_H
#define PONG_DOT_H

#define H_ZOOM_DOT  2
#define W_ZOOM_DOT  2


#include "Entity.h"

class Dot : public Entity
{

    static const int DOT_VEL = 10;

public:
    Dot(float p_x, float p_y, SDL_Texture * tex) : Entity(p_x, p_y, tex)
    {
        currentFrame.w = 32;
        currentFrame.h = 32;
        collider.h = 32 * H_ZOOM_DOT;
        collider.w = 32 * W_ZOOM_DOT;
    }

    void handleEvent( SDL_Event& e )
    {
        //If a key was pressed
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
    }

    void update()
    {
        Entity::update();
    }

    void move(int offset)
    {
        if(offset %2)
        {
            x = offset;
        }
        else
        {
            y = offset;
        }
    }

    void onCollision() override
    {
        std::cout << "Ball : Collision detected ! " << std::endl;
    }

private:
    float mVelX = 0;
    float mVelY = 0;

};


#endif //PONG_DOT_H
