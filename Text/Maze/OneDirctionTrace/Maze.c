#include "Maze.h"


void PrtMaze(int MazeSize, Maze *maze, char Charactor)
{
    int i, j;
    
    for(i=0; i<MazeSize; i++)
    {
        for(j=0; j<MazeSize; j++)
        {
            if( *(maze+(MazeSize*i)+j) )
            {
                printf("%c ", Charactor);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void PrtTrace(Pos TracePos, char Trace)
{
    gotoxy(TracePos.x*2, TracePos.y);
    printf("%c", Trace);
}

int IsFinish(Pos pos, int MazeSize)
{
    if(pos.x==MazeSize-1)
    {
        return TRUE;
    }
    return FALSE;
}

int Trace(int MazeSize, Maze *maze, Pos *TracePos)
{
    if( !IsWall(MazeSize, maze, *TracePos, 1, 0) )
    {
        *TracePos= SetPos(TracePos->x+1, TracePos->y);
        //printf("go\n");
        //printf("Positon:(%d,%d)\n", TracePos->x, TracePos->y);
        return TRUE;
    }
    
    else if( !IsWall(MazeSize, maze, *TracePos, 0, 1) )
    {
        *TracePos= SetPos(TracePos->x, TracePos->y+1);
        //printf("down\n");
        //printf("Positon:(%d,%d)\n", TracePos->x, TracePos->y);
        return TRUE;
    }
    
    else if( !IsWall(MazeSize, maze, *TracePos, 0, -1) )
    {
        *TracePos= SetPos(TracePos->x, TracePos->y-1);
        //printf("up\n");
        //printf("Positon:(%d,%d)\n", TracePos->x, TracePos->y);
        return TRUE;
    }
    
    else if( !IsWall(MazeSize, maze, *TracePos, -1, 0) )
    {
        *TracePos= SetPos(TracePos->x-1, TracePos->y);
        //printf("back\n");
        //printf("Positon:(%d,%d)\n", TracePos->x, TracePos->y);
        return TRUE;
    }
    
    else
    {
        return FALSE;
    }
}

int IsWall(int MazeSize, Maze *maze, Pos Now, int Offset_x, int Offset_y)
{
    if(Now.x<MazeSize && Now.y<MazeSize)
    {
        if( *(maze+ ( (Now.y+Offset_y)*MazeSize )+Now.x+Offset_x) )// is wall
        {
            return TRUE;
        }
    }
    return FALSE;
}

void gotoxy(int x, int y)//���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
    COORD pos = {x, y};//Ŀ���� X��ǥ���� -1 �Ѱ�. Y��ǥ���� -1�� ������ �̵�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API �Լ��Դϴ�. �̰� ���ʿ� �����
}

Pos SetPos(int x, int y)
{
    Pos pos;
    
    pos.x=x;
    pos.y=y;
    
    return pos;
}
