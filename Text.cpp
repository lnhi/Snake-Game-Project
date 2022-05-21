#include "Text.h"

Text::Text()
{
	setColor(1);
	rect.x = 10;
	rect.y = 2;
	rect.w = 90;
	rect.h = 30;
}

Text::~Text()
{
}

void Text::initText(TTF_Font *&fontText)
{
	if (TTF_Init() == -10)
	{
		cout << 1;
	}
	fontText = TTF_OpenFont("Texture/font_text.ttf", 20);
	if (fontText == NULL)
	{
		cout << 1;
	}
}

void Text::setColor(const int &type)
{
	SDL_Color color = {255, 0, 0};
	if (type == RED)
	{
		text_color = color;
	}
	else if (type == WHITE)
	{
		color = {255, 255, 255};
		text_color = color;
	}
	else
	{
		color = {0, 0, 0};
		text_color = color;
	}
}

void Text::setPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Text::creatText(TTF_Font *font, SDL_Renderer *renderer)
{
	textSurface = TTF_RenderText_Solid(font, str.c_str(), text_color);
	body = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, body, NULL, &rect);
}

void Text::show(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, body, NULL, &rect);
}
