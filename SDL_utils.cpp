#include "SDL_utils.h"
#include <iostream>
#include <windows.h>
SDL_Surface* deleteBackGroundImage(SDL_Surface* image, Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_Surface* newImage = image;
    UINT32 color_key = SDL_MapRGB(newImage->format, red, green, blue);
    SDL_SetColorKey(newImage, SDL_TRUE, color_key);
    return newImage;
}
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;
	//nap anh tu ten file (voi duong dan)
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	//Neu khong co loi, chuyen doi ve dang texture and va tra ve
	loadedImage = deleteBackGroundImage(loadedImage, 0, 0, 0);
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);}
		//dam bao viec chuyen doi khong co loi
		/*if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}*/
	return texture;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiet lap hinh chu nhat dich ma chung ta muon ve anh vao trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Dua toan bo anh trong texture vao hinh chu nhat dich
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	SDL_RenderCopy(ren, tex, NULL, &dst);
}