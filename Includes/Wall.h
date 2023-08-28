#pragma once

#ifndef PONG_WALL_H
#define PONG_WALL_H

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define H_ZOOM_WALL 3
#define W_ZOOM_WALL 2

#include "Entity.h"

class Wall : public Entity
{
    typedef struct
    {
        int X;
        int Y;
    }
            velocity;

public:
    Wall(float x, float y, SDL_Texture* tex, unsigned char p_playerNumber) :
            playerNumber(p_playerNumber),
            Entity(x, y, tex)
    {
        currentFrame.h = 64;
        currentFrame.w = 32;
        collider.h = 64 * H_ZOOM_WALL;
        collider.w = 32 * W_ZOOM_WALL;
    }
    void update()
    {
        Entity::update();
        if(collisionDetected)
        {
            getMad();
        }
        else
            getGood();

        collisionDetected = false;

        move();
    }
    void getMad()
    {
        currentFrame.x = 32;
    }
    void getGood()
    {
        currentFrame.x = 0;
    }
    void onCollision() override
    {
        std::cout << "Wall : Collision detected !" << std::endl;
        collisionDetected = true;
    }

    void handleEvent(SDL_Event& e)
    {
        if(playerNumber == 1) // Player 1
        {
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP: vel.Y -= WALL_VEL; break;
                    case SDLK_DOWN: vel.Y += WALL_VEL; break;
                }
            }
            else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP: vel.Y += WALL_VEL; break;
                    case SDLK_DOWN: vel.Y -= WALL_VEL; break;
                }
            }
        }

        else // Player 2
        {
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_z: vel.Y -= WALL_VEL; break;
                    case SDLK_s: vel.Y += WALL_VEL; break;
                }
            }
            else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_z: vel.Y += WALL_VEL; break;
                    case SDLK_s: vel.Y -= WALL_VEL; break;
                }
            }
        }

    }

    void move()
    {
        // Move the wall up or down
        y += vel.Y;

        //If the dot went too far up or down
        if( ( y < 0 ) || ( y + currentFrame.h * H_ZOOM_WALL > SCREEN_HEIGHT ) )
        {
            //Move back
            y -= vel.Y;
        }
    }

private:
    bool collisionDetected = false;
    unsigned char playerNumber;

    static const int WALL_VEL = 20;
    velocity vel = {0,0};

};


#endif //PONG_WALL_H
