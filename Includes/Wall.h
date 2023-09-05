#pragma once

#ifndef PONG_WALL_H
#define PONG_WALL_H

#include "Entity.h"
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define H_ZOOM_WALL 3
#define W_ZOOM_WALL 2

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

        Mix_AllocateChannels(1);
        beep = Mix_LoadWAV("Res/Snd/hit.wav");

/*        // Setting up the Wall's custom event
        // Triggered on collision
        WALLCOLLISIONEVENT = SDL_RegisterEvents(1);
        if(WALLCOLLISIONEVENT != -1)
        {
            SDL_memset(&WALLCOLLISIONEVENT, 0, sizeof(WALLCOLLISIONEVENT));
            collisionEvent.type = WALLCOLLISIONEVENT;
        }*/
    }

    ~Wall()
    {
        Mix_FreeChunk(beep);
    }

    void update()
    {
        Entity::update();
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

    void onCollision(CollisionState& state) override
    {
//        std::cout << "Wall : Collision detected !" << std::endl;
        Mix_PlayChannel(0, beep, 1);
/*
        collisionDetected = true;
*/
    }

    void onCollisionEnter(CollisionState &state) override
    {
        getMad();
        Mix_PlayChannel(0, beep, 1);
    }

    void onCollisionExit(CollisionState &state) override
    {
        getGood();
    }

    void handleEvent(SDL_Event& e) override
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
    static const int WALL_VEL = 15;
    velocity vel = {0,0};
    unsigned char playerNumber;
    Mix_Chunk* beep;

};


#endif //PONG_WALL_H
