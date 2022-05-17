#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>

using namespace std;

class Text
{
private:
    SDL_Rect rect;
	SDL_Texture* body;
	string str;
	SDL_Color text_color;
	SDL_Surface* textSurface;

public:
	enum TextColor {
		RED = 0,
		WHITE = 1,
		BLACK = 2,
	};
	Text();
	~Text();
	void initText(TTF_Font* &fontText);
	void setText(string t) {
		str = t;
	}
    void setSize(int w, int h){
        rect.w = w;
        rect.h = h;
    }
    void setPos(int x, int y);
	void setColor(const int& type);
	void creatText(TTF_Font* font, SDL_Renderer* renderer);
    void show(SDL_Renderer* renderer);



};