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

class RenderWindow
{
public:
    RenderWindow(const char* title, int width, int height)
            : window(nullptr), renderer(nullptr), width(width), height(height)
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
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
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
                        (int) entity.getX() * 4,
                        (int) entity.getY() * 4,
                        entity.getCurrentFrame().w * 3,
                        entity.getCurrentFrame().h * 3
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
        SDL_SetRenderDrawColor(renderer, 212, 84, 84, 255);
        SDL_RenderDrawRect(renderer, dot.getCollider());
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderCopy(renderer, dot.getTex(), &src, &dst);
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
/*         SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(renderer, entity.getCollider());
        SDL_RenderFillRect(renderer, entity.getCollider());
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); */
    }

    void display()
    {
        SDL_RenderPresent(renderer);
    }

    int getWidth() { return width; }
    int getHeight() { return height; }


private:
    SDL_Window*   window;
    SDL_Renderer* renderer;

    int width, height;
};


#endif //PONG_RENDERWINDOW_H
