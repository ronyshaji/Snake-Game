#include "player.h"

#include "SDL.h"
#include "SDL_ttf.h"

void player::getPlayerName(SDL_Window *sdl_window, SDL_Renderer *sdl_renderer)
{

    TTF_Font* font = TTF_OpenFont("Arial.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    }

    SDL_StartTextInput();
    SDL_Event e;
    while(!quit_)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit_ = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && playerName_.length() > 0) {
                playerName_.pop_back();
            }

            renderText(sdl_renderer, font, playerName_);
        }
        
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
}

void player::renderText(SDL_Renderer *sdl_renderer, TTF_Font *font, const std::string &text)
{
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(sdl_renderer);

    // Render the text
    SDL_Color textColor = {255, 255, 255}; // White text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int textWidth = 0, textHeight = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect renderQuad = {100, 100, textWidth, textHeight}; // Adjust position as needed
    SDL_RenderCopy(sdl_renderer, textTexture, NULL, &renderQuad);
    SDL_DestroyTexture(textTexture);

    // Present the rendering
    SDL_RenderPresent(sdl_renderer); 
}

std::string player::getPlayerName()
{
    return playerName_;
}