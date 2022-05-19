#ifndef SDL_UTILS__H
#define SDL_UTILS__H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>

using namespace std;
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Surface* deleteBackGroundImage(SDL_Surface* image, Uint8 red, Uint8 green, Uint8 blue);
#endif // SDL_UTILS