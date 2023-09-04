#pragma  once

#ifndef PONG_BACKGROUND_H
#define PONG_BACKGROUND_H

#include "Entity.h"

class Background : public Entity
{

public:

    Background(SDL_Texture* tex) : Entity(0, 0, tex)
    {
        currentFrame = {0,0,800,600};
    }

};



#endif //PONG_BACKGROUND_H
