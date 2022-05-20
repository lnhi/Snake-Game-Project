#ifndef POSITION_H
#define POSITION_H

enum Direction {
    UP = 0, DOWN, LEFT, RIGHT
};

struct Position
{
    int x;
    int y;

    Position(int x_, int y_) : x(x_), y(y_) {}

    Position move(Direction d)
    {
        const int dx[] = {0,0,-1,1};
        const int dy[] = {-1,1,0,0};
        return Position(x+dx[d],y+dy[d]);
    }

    bool isInsideBox(int left, int top, int width, int height) {
    
        return x >= left && x < left+width && y >= top && y < top+height;
    }
    bool isInside() 
    {
        if((x*30>=120&&x*30<=209&&y*30>=380&&y*30<=475)||(x*30>=682&&x*30<=769&&y*30>=73&&y*30<=176))
            return false;
    return true;
    }
    bool operator==(Position p) {
        return x == p.x && y == p.y;
    }
};

#endif 
