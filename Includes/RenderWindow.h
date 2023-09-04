#pragma once

#ifndef PONG_RENDERWINDOW_H
#define PONG_RENDERWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Dot.h"
#include "Wall.h"
#include "Background.h"
#include "Goal.h"
#include "ScoreManager.h"

class RenderWindow
{
public:

    RenderWindow(const char* title, int width, int height, ScoreManager& score)
            : window(nullptr), renderer(nullptr), width(width), height(height), scoreManager(&score)
    {
        window = SDL_CreateWindow(title, 500, SDL_WINDOWPOS_CENTERED,
                                  width, height, SDL_WINDOW_SHOWN);
        if(window == nullptr)
            std::cout << "SDL Window init error : " << SDL_GetError() << std::endl;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr)
            std::cout << "SDL Renderer creation error : " << SDL_GetError() << std::endl;
    }

    ~RenderWindow()
    {
        TTF_CloseFont(font);
        TTF_CloseFont(smallFont);
        SDL_FreeSurface(message);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    int getWidth() { return width; }

    int getHeight() { return height; }

    SDL_Window* getWindow() { return window; }

    SDL_Renderer* getRenderer() { return renderer; }

    SDL_Texture* loadTexture(const char* filePath)
    {
        SDL_Texture* texture = NULL;
        texture = IMG_LoadTexture(renderer, filePath);
        if(texture == NULL)
            std::cout << "SDL Texture Loading failed : " << SDL_GetError() << std::endl;
        return texture;
    }

    void clear() { SDL_RenderClear(renderer); }

    void render(Entity& entity)
    {
        SDL_Rect src
                {
                        entity.getCurrentFrame().x,
                        entity.getCurrentFrame().y,
                        entity.getCurrentFrame().w,
                        entity.getCurrentFrame().h
                };

        SDL_Rect dst
                {
                        (int) entity.getX(),
                        (int) entity.getY(),
                        entity.getCurrentFrame().w,
                        entity.getCurrentFrame().h
                };


        SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);


    }

    void render(Dot& dot)
    {
        SDL_Rect src
                {
                        dot.getCurrentFrame().x,
                        dot.getCurrentFrame().y,
                        dot.getCurrentFrame().w,
                        dot.getCurrentFrame().h
                };

        SDL_Rect dst
                {
                        (int) dot.getX(),
                        (int) dot.getY(),
                        dot.getCurrentFrame().w * W_ZOOM_DOT,
                        dot.getCurrentFrame().h * H_ZOOM_DOT
                };
/*        SDL_SetRenderDrawColor(renderer, 212, 84, 84, 255);
        SDL_RenderDrawRect(renderer, dot.getCollider());
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
        SDL_RenderCopy(renderer, dot.getTex(), &src, &dst);
    }

    void renderEX(Dot& dot)
    {
        SDL_Rect src
                {
                        dot.getCurrentFrame().x,
                        dot.getCurrentFrame().y,
                        dot.getCurrentFrame().w,
                        dot.getCurrentFrame().h
                };

        SDL_Rect dst
                {
                        SCREEN_WIDTH/2 - src.w,
                        SCREEN_HEIGHT/2 - src.h,
                        dot.getCurrentFrame().w * W_ZOOM_DOT * 2,
                        dot.getCurrentFrame().h * H_ZOOM_DOT * 2
                };
/*      SDL_SetRenderDrawColor(renderer, 212, 84, 84, 255);
        SDL_RenderDrawRect(renderer, dot.getCollider());
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
        SDL_RenderCopyEx(renderer,dot.getTex(), &src, &dst, offset % 360, nullptr, SDL_FLIP_NONE);
    }

    void render(Wall& entity)
    {

        SDL_Rect src
                {
                        entity.getCurrentFrame().x,
                        entity.getCurrentFrame().y,
                        entity.getCurrentFrame().w,
                        entity.getCurrentFrame().h
                };


        SDL_Rect dst
                {
                        (int) entity.getX(),
                        (int) entity.getY(),
                        entity.getCurrentFrame().w * W_ZOOM_WALL,
                        entity.getCurrentFrame().h * H_ZOOM_WALL

                };

        SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
/*      SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(renderer, entity.getCollider());
        SDL_RenderFillRect(renderer, entity.getCollider());
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
    }

    void render(Goal& goal)
    {
        SDL_Rect src
                {
                        goal.getCurrentFrame().x,
                        goal.getCurrentFrame().y,
                        goal.getCurrentFrame().w,
                        goal.getCurrentFrame().h
                };

        SDL_Rect dst
                {
                        (int) goal.getX(),
                        (int) goal.getY(),
                        goal.getCurrentFrame().w,
                        goal.getCurrentFrame().h
                };


//      SDL_RenderCopy(renderer, goal.getTex(), &src, &dst);
        SDL_RenderFillRect(renderer, goal.getCollider());
    }

    void render(Background& background)
    {
        SDL_Rect src
                {
                        background.getCurrentFrame().x + offset % (48 * 8),
                        background.getCurrentFrame().y + offset % (44 * 6),
                        background.getCurrentFrame().w / 2,
                        background.getCurrentFrame().h / 2
                };

        SDL_Rect dst
                {
                        (int) background.getX(),
                        (int) background.getY(),
                        background.getCurrentFrame().w ,
                        background.getCurrentFrame().h
                };


        SDL_RenderCopy(renderer, background.getTex(), &src, &dst);


        offset++;


    }

    void renderTitle(float x, float y, const char* text)
    {
        message = TTF_RenderText_Blended(font, text, colours[4]);
        SDL_Surface* messagebg = TTF_RenderText_Blended(font, text, colours[0]);
        SDL_Texture* messageTex = SDL_CreateTextureFromSurface(renderer, message);
        SDL_Texture* bgTex = SDL_CreateTextureFromSurface(renderer,messagebg);
        SDL_Rect fgsrc
                {
                        0,
                        0,
                        message->w,
                        message->h

                };

        SDL_Rect fgdst
                {
                        (int)x,
                        (int)y,
                        fgsrc.w,
                        fgsrc.h
                };

        SDL_Rect bgsrc
                {
                        0,
                        0,
                        message->w,
                        message->h

                };

        SDL_Rect bgdst
                {
                        fgdst.x - 3,
                        fgdst.y + 3,
                        bgsrc.w,
                        bgsrc.h
                };


        SDL_RenderCopy(renderer, bgTex, &bgsrc, &bgdst);
        SDL_RenderCopy(renderer, messageTex, &fgsrc, &fgdst);
        SDL_FreeSurface(messagebg);
    }

    void render(float x, float y, const char* text)
    {
        message = TTF_RenderText_Blended(smallFont, text, colours[4]);
        SDL_Surface* messagebg = TTF_RenderText_Blended(smallFont, text, colours[0]);
        SDL_Texture* messageTex = SDL_CreateTextureFromSurface(renderer, message);
        SDL_Texture* bgTex = SDL_CreateTextureFromSurface(renderer,messagebg);
        SDL_Rect fgsrc
                {
                        0,
                        0,
                        message->w,
                        message->h

                };

        SDL_Rect fgdst
                {
                        (int)x,
                        (int)y,
                        fgsrc.w,
                        fgsrc.h
                };

        SDL_Rect bgsrc
                {
                        0,
                        0,
                        message->w,
                        message->h

                };

        SDL_Rect bgdst
                {
                        fgdst.x - 3,
                        fgdst.y + 3,
                        bgsrc.w,
                        bgsrc.h
                };


        SDL_RenderCopy(renderer, bgTex, &bgsrc, &bgdst);
        SDL_RenderCopy(renderer, messageTex, &fgsrc, &fgdst);
        SDL_FreeSurface(messagebg);
    }

    void renderScore()
    {
        SDL_Surface* player1Score = TTF_RenderText_Blended(smallFont, scoreManager->getPlayer1ScoreAsString(), colours[4]);
        SDL_Surface* player1Scorebg = TTF_RenderText_Blended(smallFont, scoreManager->getPlayer1ScoreAsString(), colours[0]);
        SDL_Surface* player2Score = TTF_RenderText_Blended(smallFont, scoreManager->getPlayer2ScoreAsString(), colours[4]);
        SDL_Surface* player2Scorebg = TTF_RenderText_Blended(smallFont, scoreManager->getPlayer2ScoreAsString(), colours[0]);

        SDL_Texture* player1ScoreTex = SDL_CreateTextureFromSurface(renderer, player1Score);
        SDL_Texture* player1ScoreTexbg = SDL_CreateTextureFromSurface(renderer, player1Scorebg);
        SDL_Texture* player2ScoreTex = SDL_CreateTextureFromSurface(renderer, player2Score);
        SDL_Texture* player2ScoreTexbg = SDL_CreateTextureFromSurface(renderer, player2Scorebg);


        SDL_Rect player1FGSrc
        {
                0,
                0,
                player1Score->w,
                player1Score->h
        };

        SDL_Rect player1FGDst
        {
                (int)100,
                (int)50,
                player1FGSrc.w,
                player1FGSrc.h
        };

        SDL_Rect player1BGSrc
        {
                0,
                0,
                player1Score->w,
                player1Score->h

        };

        SDL_Rect player1BGDst
        {
                player1FGDst.x - 3,
                player1FGDst.y + 3,
                player1BGSrc.w,
                player1BGSrc.h
        };

        SDL_Rect player2FGSrc
                {
                    0,
                    0,
                    player2Score->w,
                    player2Score->h
                };

        SDL_Rect player2FGDst
                {
                        (int)700,
                        (int)50,
                        player2FGSrc.w,
                        player2FGSrc.h
                };

        SDL_Rect player2BGSrc
                {
                        0,
                        0,
                        player2Scorebg->w,
                        player2Scorebg->h

                };

        SDL_Rect player2BGDst
                {
                        player2FGDst.x - 3,
                        player2FGDst.y + 3,
                        player2BGSrc.w,
                        player2BGSrc.h
                };

        SDL_RenderCopy(renderer, player1ScoreTexbg, &player1BGSrc, &player1BGDst);
        SDL_RenderCopy(renderer, player1ScoreTex, &player1FGSrc, &player1FGDst);
        SDL_RenderCopy(renderer, player2ScoreTexbg, &player2BGSrc, &player2BGDst);
        SDL_RenderCopy(renderer, player2ScoreTex, &player2FGSrc, &player2FGDst);


        SDL_FreeSurface(player1Score);
        SDL_FreeSurface(player2Score);
        SDL_FreeSurface(player1Scorebg);
        SDL_FreeSurface(player2Scorebg);


    }

    void display()
    {
        SDL_RenderPresent(renderer);
    }


private:
    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Surface* message;
    SDL_Color colours[5] = {{0,0,0,200},
                            {105, 106, 106, 255},
                            {48, 96, 130, 255},
                            { 55, 148, 110, 255},
                            { 55, 175, 140, 220}};
    TTF_Font* font = TTF_OpenFont("Res/fonts/Kaph-Regular.ttf",76);
    TTF_Font* smallFont = TTF_OpenFont("Res/fonts/Kaph-Italic.ttf", 28);
    ScoreManager* scoreManager;
    int offset = 1;
    int width, height;
};


#endif //PONG_RENDERWINDOW_H
