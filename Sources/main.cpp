#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../Includes/Entity.h"
#include "../Includes/CollisionManager.h"
#include "../Includes/Wall.h"
#include "../Includes/RenderWindow.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

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
    Goal leftGoal(0, 0, true, scoreManager), rightGoal(SCREEN_WIDTH - 50, 0, false, scoreManager);

    CollisionManager collisionManager;
    collisionManager.Register(ball);
    collisionManager.Register(wall);
    collisionManager.Register(walter);
    collisionManager.Register(leftGoal);
    collisionManager.Register(rightGoal);

    bool run = true, mainTitle = true, gameOver = false;
    SDL_Event e;

    float timeSinceGameLoop = 0.0f;

    while (run) {

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                run = false;

            if(e.key.keysym.sym == SDLK_RETURN && mainTitle)
            {
                mainTitle = false;
                timeSinceGameLoop = SDL_GetTicks();
            }

            if(e.key.keysym.sym == SDLK_RETURN && gameOver)
            {
                run = false;
            }

            if(!mainTitle && !gameOver)
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
        else if(!mainTitle && !gameOver)
        {
            renderWin.clear();

            // Prevent stupid init collisions
            if(SDL_GetTicks() >= timeSinceGameLoop + 0.02f)
                collisionManager.checkCollisions();

            if(scoreManager.checkForWinner())
                gameOver = true;

            ball.update();
            wall.update();
            walter.update();

            renderWin.render(background);
            renderWin.renderScore();
            renderWin.render(ball);
            renderWin.render(wall);
            renderWin.render(walter);
            renderWin.display();
        }

        else // Game Over
        {
            renderWin.clear();
            renderWin.render(background);
            renderWin.renderTitle(SCREEN_WIDTH / 2 - 320, 150 + (25 * sin(SDL_GetTicks() * 0.002)), "Shitty Pong");
            renderWin.render(190, 500 + (25 * sin(SDL_GetTicks() * 0.002)), "GAME OVER");
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
