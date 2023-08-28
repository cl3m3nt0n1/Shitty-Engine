#include <SDL2/SDL.h>
#include <iostream>

#include "../Includes/Entity.h"
#include "../Includes/CollisionManager.h"
#include "../Includes/Wall.h"
#include "../Includes/Dot.h"
#include "../Includes/RenderWindow.h"



#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600


int main() {

    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER ) > 0)
    {
        std::cout << "SDL Init error : " << SDL_GetError() << std::endl;
    }

    //Creating a window
    RenderWindow renderWin("SDL2 Test", SCREEN_WIDTH, SCREEN_HEIGHT);

    float initTime = 0.0f, deltaTime = 0.0f, timeSinceStart = 0.0f;

    SDL_Texture* ballTexture = renderWin.loadTexture("Res/Gfx/ball.png");
    SDL_Texture* wallTexture = renderWin.loadTexture("Res/Gfx/wall.png");

    CollisionManager collisionManager;

    Dot ball(0, 0, ballTexture);
    Wall wall(350, 200, wallTexture, 1), walter(100, 200, wallTexture, 2);

    collisionManager.Register(ball);
    collisionManager.Register(wall);
    collisionManager.Register(walter);


    int mouseX = 0, mouseY = 0;

    bool run = true;
    SDL_Event e;

    while (run) {

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                run = false;

            wall.handleEvent(e);
            walter.handleEvent(e);
        }

        renderWin.clear();

        SDL_GetMouseState(&mouseX, &mouseY);
        ball.setX(mouseX);
        ball.setY(mouseY);

        collisionManager.checkCollisions();

        ball.update();
        wall.update();
        walter.update();

        renderWin.render(ball);
        renderWin.render(wall);
        renderWin.render(walter);
        renderWin.display();
    }

    SDL_Quit();

    return 0;
}
