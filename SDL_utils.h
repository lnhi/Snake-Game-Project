#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <windows.h>

using namespace std;

void logSDLError(std::ostream &os, const std::string &msg, bool fatal);
void initSDL(SDL_Window *&window, SDL_Renderer *&renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const string &WINDOW_TITLE);
void quitSDL(SDL_Window *window, SDL_Renderer *renderer);
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Surface *deleteBackGroundImage(SDL_Surface *image, Uint8 red, Uint8 green, Uint8 blue);
void waitUntilKeyPressed();

#endif // SDL_UTILS