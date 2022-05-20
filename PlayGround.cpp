#include <vector>
#include <cassert>
#include <cstdlib>
#include "PlayGround.h"

using namespace std;

PlayGround::PlayGround(int width, int height)
    : squares(height, vector<CellType>(width, CELL_EMPTY)),
      snake(this),
      status(GAME_RUNNING),
      score(0)
{
    addCherry();
}

PlayGround::~PlayGround()
{
   
}

void PlayGround::changeCellState(Position pos, CellType type)
{
    assert(pos.isInsideBox(0,0,getWidth(),getHeight()));
    squares[pos.y][pos.x] = type;
}

void PlayGround::processUserInput(UserInput input)
{
    snake.processUserInput(input);
}

void PlayGround::nextStep()
{
    snake.nextStep();
}

void PlayGround::addCherry()
{
    vector<int>v;
    vector<int>u;
      for(int i=2; i<=30; i++)
        if((i<=3||i>=7)&&(i<=21||i>=26))
            v.push_back(i);
    for(int i=2; i<=20; i++)
        if((i<=11||i>=16)&&(i<=1||i>=6))
            u.push_back(i);
    int wid=v.size();
    int hei=u.size();
    do {
        Position p(rand()%wid, rand()%hei);
        if (getCellState(p) == CELL_EMPTY) 
        {
            changeCellState(p, CELL_CHERRY);
            break;
        }
    } while (true);
}

void PlayGround::setGameStatus(GameStatus status)
{
    this->status = status;
}

vector<Position> PlayGround::getSnakePositions() const
{
    vector<Position> res;
    for (SnakeNode* p = snake.getHead(); p != nullptr; p = p->next)
        res.push_back(p->position);
    return res;
}
