#ifndef GALLERY_H
#define GALLERY_H
#include <vector>
#include <SDL2/SDL.h>

#include "SDL_utils.h"
#include "painter.h"

using namespace std;

enum PictureID
{
    PIC_FRUIT = 0,
    PIC_SNAKE_VERTICAL,
    PIC_SNAKE_HORIZONTAL,
    PIC_SNAKE_HEAD,
    PIC_SNAKE_CORNER1,
    PIC_SNAKE_CORNER2,
    PIC_SNAKE_CORNER3,
    PIC_SNAKE_CORNER4,
};

class Gallery
{
    vector<SDL_Texture *> pictures;
    Painter &painter;

public:
    Gallery(Painter &painter_);
    ~Gallery();
    void loadGamePictures();
    SDL_Texture *getImage(PictureID id) const { return pictures[id]; }
};

#endif
