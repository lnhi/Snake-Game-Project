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
#include "Text.h"
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

double STEP_DELAY = 0.15;
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

int main(int argc, char* argv[])
{
    srand(time(0));
   
    initSDL(window, renderer);
    Painter painter(window, renderer);
    gallery = new Gallery(painter);
    PlayGround playGround(GROUND_WIDTH, GROUND_HEIGHT);
    auto start = CLOCK_NOW();
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    gMusic=Mix_LoadMUS("Texture/bksound.wav");
    Mix_Chunk* click = NULL;
    click = Mix_LoadWAV("Texture/click.wav");
    Mix_PlayMusic(gMusic,-1);
homee:
    SDL_RenderClear(renderer);
    SDL_Texture* newTexture =loadTexture("Texture/startgame.png",renderer);
    renderTexture(newTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(painter.getRenderer());

     SDL_Texture* helpTexture =loadTexture("Texture/help_button.png",renderer);
    renderTexture(helpTexture, renderer, 48, 430 , 165, 75);
    SDL_RenderPresent(painter.getRenderer());

    SDL_Texture* startTexture = loadTexture("Texture/play_button.png",renderer);
    renderTexture(startTexture, renderer,716, 430, 160, 75);
    SDL_RenderPresent(painter.getRenderer());
 
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
    cout<<playGround.getHeight()<<endl;
    if(choice==1)
    {
    Mix_PlayChannel (-1, click, 0);
    SDL_Texture* newTexture = loadTexture("Texture/help.png",renderer);
    SDL_RenderCopy(renderer, newTexture, NULL, NULL);
    SDL_RenderPresent(painter.getRenderer());
    SDL_Event e2;
    int choice2;
            while (true) {
            SDL_Delay(10);
            if ( SDL_WaitEvent(&e2) == 0) continue;
            if (e2.type == SDL_QUIT) break;
            if (e2.type == SDL_KEYDOWN && e2.key.keysym.sym == SDLK_ESCAPE) break;
            if (e2.type == SDL_MOUSEBUTTONDOWN) {
                filled_rect.x = e2.button.x; // Lấy hoành độ x của chuột
                filled_rect.y = e2.button.y; // Lấy tung độ y của chuột
                if (filled_rect.x >= 140 && filled_rect.y >= 35 && filled_rect.x <= 177 && filled_rect.y <= 125)
                {
                        choice2 = 1;
                        break;
                }
                }
            } 
    if(choice2==1)
    {
     Mix_PlayChannel (-1, click, 0);
     goto homee;
    }
    }
    if(choice==2)
    {
    Mix_PlayChannel (-1, click, 0);
    SDL_Event e;
    SDL_Texture* newTexture =loadTexture("Texture/bk_gr1.png",renderer);
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
        int t=playGround.getScore();
        STEP_DELAY-=0.0000001;
        //cout<<STEP_DELAY<<endl;
        if (elapsed.count() > STEP_DELAY)
        {
            playGround.nextStep();
            renderGamePlay(painter, playGround);
            score.setText("Score: " + to_string(playGround.getScore()));
            score.creatText(fontText, painter.getRenderer());
            SDL_RenderPresent(painter.getRenderer());
            start = end;
        }
        SDL_Delay(1);
    }
    renderGameOver(painter, playGround, to_string(playGround.getScore()));
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

/*void renderSplashScreen(Painter& painter, const PlayGround& playGround)
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
 */
void drawCherry(Painter& painter, int left, int top)
{
    SDL_Rect dst = { left+5, top+5, CELL_SIZE, CELL_SIZE};
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
        SDL_Rect dst = { left+pos[i].x*CELL_SIZE+1, top+pos[i].y*CELL_SIZE+1, CELL_SIZE+2, CELL_SIZE+2};
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
    score.setSize(35,50);
    score.setPos(120, 485);
    score.setText(lastScore);
    
    SDL_Texture* newTexture = painter.loadTexture("Texture/gameover.png");
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
    /*SDL_Event e;
    int choice=-1;
            while (true) {
            SDL_Delay(10);
            if ( SDL_WaitEvent(&e3) == 0) continue;
            if (e3.type == SDL_QUIT) break;
            if (e3.type == SDL_KEYDOWN && e2.key.keysym.sym == SDLK_ESCAPE) break;
            if (e3.type == SDL_MOUSEBUTTONDOWN) {
                filled_rect.x = e3.button.x; // Lấy hoành độ x của chuột
                filled_rect.y = e3.button.y; // Lấy tung độ y của chuột
                if (filled_rect.x >= 140 && filled_rect.y >= 35 && filled_rect.x <= 177 && filled_rect.y <= 125)
                {
                        choice= 1;
                        break;
                }
                }
            } 
    if(choice==1)
    goto homee;*/
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
 
