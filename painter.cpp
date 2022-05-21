#include "painter.h"

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

Painter::Painter(SDL_Window *window, SDL_Renderer *renderer_)
    : renderer(renderer_)
{
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0)
        SDL_GetWindowSize(window, &width, &height);

    setPosition(width / 2, height / 2);
    setAngle(0);
    setColor(WHITE_COLOR);
    clearWithBgColor(BLUE_COLOR);
}

void Painter::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Painter::setAngle(float angle)
{
    this->angle = angle - floor(angle / 360) * 360;
}
void Painter::setColor(SDL_Color color)
{
    this->color = color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}
void Painter::clearWithBgColor(SDL_Color bgColor)
{
    SDL_Color curColor = color;
    setColor(bgColor);
    SDL_RenderClear(renderer);
    setColor(curColor);
}
SDL_Texture *Painter::loadTexture(string path)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    loadedSurface = deleteBackGroundImage(loadedSurface, 166, 211, 136);
    if (loadedSurface == NULL)
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
bool Painter::createImage(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect)
{
    if (texture == NULL)
        return false;
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
    return true;
}
