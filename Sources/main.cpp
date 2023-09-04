#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../Includes/Entity.h"
#include "../Includes/CollisionManager.h"
#include "../Includes/Wall.h"
#include "../Includes/Dot.h"
#include "../Includes/ScoreManager.h"
#include "../Includes/RenderWindow.h"


/*
 * TODO :
 *      - Main Title screen X
 *      - Score
 *      - Game Over Screen
 *      - Sounds X
 * */


#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

float getTimeInSeconds()
{
    return SDL_GetTicks() * 0.001;
}

bool init()
{
    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER ) > 0)
    {
        std::cout << "SDL Init error : " << SDL_GetError() << std::endl;
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        std::cout << "SDL Mixer Error : " << Mix_GetError() << std::endl;
        return false;
    }
    if(TTF_Init() == -1)
    {
        std::cout << "SDL TTF init error " << TTF_GetError() << std::endl;
        return false;
    }
    return true;

}

int main() {

    if(!init())
        exit(-1);

    float initTime = 0.0f, deltaTime = 0.0f, timeSinceStart = 0.0f;

    ScoreManager scoreManager;

    // Loading BGMusic
    Mix_Music * backgroundTrack = Mix_LoadMUS("Res/Snd/amiga.mod");
    Mix_PlayMusic(backgroundTrack, -1);

    //Creating a window
    RenderWindow renderWin("SDL2 Test", SCREEN_WIDTH, SCREEN_HEIGHT, scoreManager);

    SDL_Texture* ballTexture = renderWin.loadTexture("Res/Gfx/ball.png");
    SDL_Texture* wallTexture = renderWin.loadTexture("Res/Gfx/wall.png");
    SDL_Texture * backgroundTex = renderWin.loadTexture("Res/Gfx/background.png");

    Background background(backgroundTex);
    Dot ball(200, 300, ballTexture);
    Wall wall(650, 200, wallTexture, 1), walter(100, 200, wallTexture, 2);
    Goal leftGoal(0, 0), rightGoal(SCREEN_WIDTH - 50, 0);

    CollisionManager collisionManager(scoreManager);
    collisionManager.Register(ball);
    collisionManager.Register(wall);
    collisionManager.Register(walter);
    collisionManager.RegisterDoatAndGoals(ball,leftGoal,rightGoal);

    bool run = true, mainTitle = true;
    SDL_Event e;

    while (run) {

        timeSinceStart = getTimeInSeconds();
        deltaTime = timeSinceStart - initTime;
        initTime = timeSinceStart;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                run = false;
            if(e.key.keysym.sym == SDLK_RETURN && mainTitle)
            {
                mainTitle = false;
            }


            if(!mainTitle)
            {
                wall.handleEvent(e);
                walter.handleEvent(e);
            }

        }

        // Title screen
        if(mainTitle)
        {
            renderWin.clear();
            renderWin.render(background);
            renderWin.renderTitle(SCREEN_WIDTH / 2 - 320, 150 + (25 * sin(SDL_GetTicks() * 0.002)), "Shitty Pong");
            renderWin.render(190, 500, "Press Enter to play!");
            renderWin.renderEX(ball);
            renderWin.display();
        }

        // Main Game loop
        else
        {
            renderWin.clear();

            collisionManager.checkCollisions();
            collisionManager.checkCollisionsDotToGoal();

            ball.update(deltaTime);
            wall.update();
            walter.update();

            renderWin.render(background);
            renderWin.renderScore();
            renderWin.render(leftGoal);
            renderWin.render(rightGoal);
            renderWin.render(ball);
            renderWin.render(wall);
            renderWin.render(walter);
            renderWin.display();
        }
    }

    Mix_FreeMusic(backgroundTrack);
    Mix_CloseAudio();
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(wallTexture);
    SDL_Quit();

    return 0;
}
