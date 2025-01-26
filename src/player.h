#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"

class player
{
    public:
        std::string getPlayerName();
    private:
        std::string playerName_{" "};
        bool quit_ = false;

        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        void getPlayerName(SDL_Window *sdl_window, SDL_Renderer *sdl_renderer);
        void renderText(SDL_Renderer *sdl_renderer, TTF_Font* font, const std::string &text);

};

#endif