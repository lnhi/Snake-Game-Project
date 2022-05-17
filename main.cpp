#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <ctime>
#include <cmath>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
 
#include "painter.h"
#include "PlayGround.h"
#include "Gallery.h"
#include"Text.h"

//#include "splash.h"
#include "display.h"
#include "SDL_utils.h"

using namespace std;
 
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake Game";
 
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* gscreen;
const int GROUND_WIDTH = 30;
const int GROUND_HEIGHT = 20;
const int CELL_SIZE = 30;

const double STEP_DELAY = 0.1;
#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

TTF_Font *gFont=NULL;
Mix_Music *gMusic=NULL;
void logSDLError(std::ostream& os,const std:: string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
 
void renderSplashScreen(Painter& painter, const PlayGround& playGround);
void renderGamePlay(Painter&, const PlayGround& playGround);
void renderGameOver(Painter&, const PlayGround& playGround, string lastScore);
UserInput interpretEvent(SDL_Event e);
void updateRankingTable(const PlayGround& playGround);
 
Gallery* gallery = nullptr;
/*
bool loadFromREnderer(string textureText, SDL_Color textColor)
{
  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText,c_str(), textColor);
  if(textSurface==NULL)
  {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }
  else 
  {
      newTexture=SDL_CreateTextureFromSurface(renderer, textSurface);
      if(newTexture==NULL)
      {
          printf("unable to create textture from rendered text! SDL Error: %s\n", SDL_GetError());
      }
      SDL_FreeSurface(textSurface);
  }
  return newTexture!=NULL;
}
void free()
{}
void setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(newTextture, red, green, blue);
}
void setBlenMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(newTexture, blending);
}
void setAlpha(Uint 8 alpha)
{
    SDL_SetTextureAlphaMod(newTexture, alpha);
}
void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    SDL_Rect renderQuad={x, y, SCREEN_WIDTH, SCREEN_HEIGHT};
    if(clip!=NULL)
    {
        renderQuad.w = clip ->w;
        renderQuad.h = clip ->h;
    }

    SDL_RenderCopyEx(renderder, newTexure, clip, &renderQuad, angle, center, flip);
}*/
int main(int argc, char* argv[])
{
    srand(time(0));
   
    initSDL(window, renderer);
    Painter painter(window, renderer);
    gallery = new Gallery(painter);
    PlayGround playGround(GROUND_WIDTH, GROUND_HEIGHT);
   // renderSplashScreen(painter, playGround);
   
    auto start = CLOCK_NOW();

    SDL_Texture* newTexture =loadTexture("Texture/startgame.png",renderer);
    renderTexture(newTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(painter.getRenderer());

    SDL_Texture* helpTexture =loadTexture("Texture/help_button.png",renderer);
    renderTexture(helpTexture, renderer, 48, 430 , 165, 75);
    SDL_RenderPresent(painter.getRenderer());

    SDL_Texture* startTexture = loadTexture("Texture/play_button.png",renderer);
    renderTexture(startTexture, renderer,716, 430, 160, 75);
    SDL_RenderPresent(painter.getRenderer());

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    gMusic=Mix_LoadMUS("Texture/bksound.wav");
    Mix_PlayMusic(gMusic,-1);

    int choice=-1;
    SDL_Event e1;
    SDL_Rect filled_rect;
    while(true)
    {
        SDL_Delay(10);
        if(SDL_WaitEvent(&e1)==0) continue;
        if(e1.type==SDL_QUIT) break;
        if(e1.type==SDL_KEYDOWN && e1.key.keysym.sym==SDLK_ESCAPE) break;
        if(e1.type ==SDL_MOUSEBUTTONDOWN)
        {
            filled_rect.x=e1.button.x;
            filled_rect.y=e1.button.y;
            if(filled_rect.x >=48 && filled_rect.y>=430 && filled_rect.x<=213 && filled_rect.y<=505)
            {
                choice=1;
                break;
            }
            if(filled_rect.x >=716 && filled_rect.y>=430 && filled_rect.x<=876 && filled_rect.y<=505)
            {
                choice=2;
                break;
            }

       }
    }
    cout<<choice;
    if(choice==1)
    {
    SDL_Texture* newTexture = loadTexture("Texture/help.png",renderer);
    SDL_RenderCopy(renderer, newTexture, NULL, NULL);
    SDL_RenderPresent(painter.getRenderer());
    SDL_Event e2;
    while (true) 
    {
        if ( SDL_WaitEvent(&e2) != 0 &&
             (e2.type == SDL_KEYDOWN || e2.type == SDL_QUIT) )
                break;
    }  
    }
    if(choice==2)
    {
    SDL_Event e;
    SDL_Texture* newTexture =loadTexture("Texture/bk_gr.png",renderer);
    renderTexture(newTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(painter.getRenderer());
    TTF_Font* fontText = NULL;
    Text score;
    score.initText(fontText);
    score.setText("Score:");

     while (playGround.isGameRunning())
    {
        SDL_RenderCopy(renderer, newTexture, NULL, NULL);
        while (SDL_PollEvent(&e))
        {
            UserInput input = interpretEvent(e);
            playGround.processUserInput(input);
        }
        auto end = CLOCK_NOW();
        ElapsedTime elapsed = end-start;
        if (elapsed.count() > STEP_DELAY)
        {
            playGround.nextStep();
            renderGamePlay(painter, playGround);
            score.setText("Score: " + playGround.getScore());
            score.creatText(fontText, painter.getRenderer());
            SDL_RenderPresent(painter.getRenderer());
            start = end;
        }
        SDL_Delay(1);
    }
    renderGameOver(painter, playGround, playGround.getScore());
    updateRankingTable(playGround);
    
    delete gallery;
    quitSDL(window, renderer);
    }
    return 0;
}
 
void logSDLError(std::ostream& os, const std:: string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
 
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
 
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
 
    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);
 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);
 
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
 
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    Mix_FreeMusic(gMusic);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
/*bool loadMedia()
{
    //Loading success flag
    bool success = true;
    //Load PNG surface
    gPNGSurface = loadSurface( "bk_gr.png" );
    if( gPNGSurface == NULL )
    {
        printf( "Failed to load PNG image!\n" );
        success = false;
    }
    return success;
}
SDL_Surface* loadSurface(string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;
 
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
 
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
 
    return optimizedSurface;
}*/
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
 
float generateRandomNumber()
{
    return (float) rand() / RAND_MAX;
}

void renderSplashScreen(Painter& painter, const PlayGround& playGround)
{
    SDL_Texture* newTexture = painter.loadTexture("startgame.png");
    SDL_RenderCopy(renderer, newTexture, NULL, NULL);
    SDL_RenderPresent(painter.getRenderer());
    SDL_Event e;
    while (true) 
    {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
                break;
    }  
}
 
void drawCherry(Painter& painter, int left, int top)
{
    SDL_Rect dst = { left+5, top+5, CELL_SIZE+5, CELL_SIZE+5};
    painter.createImage(gallery->getImage(PIC_CHERRY), NULL, &dst);
}
void drawBox(Painter& painter, int left, int top)
{
    SDL_Rect dst = { left+5, top+5, CELL_SIZE+5, CELL_SIZE+5};
    painter.createImage(gallery->getImage(PIC_BOX), NULL, &dst);
}
void drawSnake(Painter& painter, int left, int top, vector<Position> pos)
{
    for (size_t i = 0; i < pos.size(); i++)
    {
        SDL_Rect dst = { left+pos[i].x*CELL_SIZE+1, top+pos[i].y*CELL_SIZE+1, CELL_SIZE+5, CELL_SIZE+5};
        SDL_Texture* texture = NULL;
        if (i > 0)
        {
            if(pos[i].y == pos[i+1].y && pos[i].x < pos[i+1].x && pos[i].y < pos[i-1].y && pos[i].x == pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER1);
            }
            else if(pos[i].y < pos[i+1].y && pos[i].x == pos[i+1].x && pos[i].y == pos[i-1].y && pos[i].x > pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER2);
            }
            else if(pos[i].y == pos[i+1].y && pos[i].x > pos[i+1].x && pos[i].y > pos[i-1].y && pos[i].x == pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER3);
            }
            else if(pos[i].y > pos[i+1].y && pos[i].x == pos[i+1].x && pos[i].y == pos[i-1].y && pos[i].x < pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER4);
            }
            else if(pos[i].y < pos[i+1].y && pos[i].x == pos[i+1].x && pos[i].y == pos[i-1].y && pos[i].x < pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER1);
            }
            else if(pos[i].y == pos[i+1].y && pos[i].x > pos[i+1].x && pos[i].y < pos[i-1].y && pos[i].x == pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER2);
            }
            else if(pos[i].y > pos[i+1].y && pos[i].x == pos[i+1].x && pos[i].y == pos[i-1].y && pos[i].x > pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER3);
            }
            else if(pos[i].y == pos[i+1].y && pos[i].x < pos[i+1].x && pos[i].y > pos[i-1].y && pos[i].x == pos[i-1].x){
                texture = gallery->getImage(PIC_SNAKE_CORNER4);
            }
            else{
                if (pos[i].y == pos[i-1].y)
                {
                    texture = gallery->getImage(PIC_SNAKE_HORIZONTAL);
                }
                else{
                    texture = gallery->getImage(PIC_SNAKE_VERTICAL);        
                }    
            }

        }
        else
        {
            texture = gallery->getImage(PIC_SNAKE_HEAD);
        }
        painter.createImage(texture, NULL, &dst);
    }
   
}

void renderGamePlay(Painter& painter, const PlayGround& playGround)
{

    int top = 0, left = 0;
    int width = playGround.getWidth();
    int height = playGround.getHeight();
    drawBox(painter, 30, 30);
    const vector<vector<CellType> >& squares = playGround.getSquares();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (squares[i][j] == CELL_CHERRY)
                drawCherry(painter, left+j*CELL_SIZE, top+i*CELL_SIZE);
 
    vector<Position> snakePositions = playGround.getSnakePositions();
    
    drawSnake(painter, left, top, snakePositions);
    
}
void renderGameOver(Painter& painter, const PlayGround& playGround, string lastScore)
{
    TTF_Font* fontText = NULL;
    Text score;
    score.initText(fontText);
    score.setSize(150,50);
    score.setPos(380, 438);
    score.setText("Your Score: " + lastScore);
    
    SDL_Texture* newTexture = painter.loadTexture("gameover.png");
    SDL_RenderCopy(renderer, newTexture, NULL, NULL);
    
    score.creatText(fontText, painter.getRenderer());
    SDL_RenderPresent(painter.getRenderer());
    SDL_Event e;
    while (true) 
    {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
                break;
    }  
}
 
UserInput interpretEvent(SDL_Event e)
{
    if (e.type == SDL_KEYUP)
     {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: return KEY_UP;
        case SDLK_DOWN: return KEY_DOWN;
        case SDLK_LEFT: return KEY_LEFT;
        case SDLK_RIGHT: return KEY_RIGHT;
        }
    }
    return NO_INPUT;
}
 
void updateRankingTable(const PlayGround& playGround)
{
 
}
 
