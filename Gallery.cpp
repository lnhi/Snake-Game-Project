#include "Gallery.h"

Gallery::Gallery(Painter& painter_)
    : painter(painter_)
{
    loadGamePictures();
}

Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
}

void Gallery::loadGamePictures()
{
    pictures.push_back(painter.loadTexture("Texture/fruit.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_vertical.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_horizontal.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_head.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_corner1.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_corner2.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_corner3.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_corner4.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_stub_hor.png"));
    pictures.push_back(painter.loadTexture("Texture/snake_stub_ver.png"));
    pictures.push_back(painter.loadTexture("Texture/box.png"));
}
