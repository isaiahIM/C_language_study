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

void CloneMaze(int MazeSize, const Maze *Original, Maze *Clone)
{
    int i, j;
    
    for(i=0; i<MazeSize; i++)
    {
        for(j=0; j<MazeSize; j++)
        {
           *(Clone+(MazeSize*i)+j)= *(Original+(MazeSize*i)+j);
        }
    }
}

void PrtTrace(Pos TracePos, Pos *HistoryPos, char Trace)
{
    gotoxy(TracePos.x*2, TracePos.y);
    printf("%c", Trace);
    
    if(HistoryPos!=NULL)
    {
        gotoxy( (HistoryPos->x)*2, HistoryPos->y);
        printf(" ");
    }
}

int IsFinish(Pos pos, int MazeSize)
{
    if(pos.x==MazeSize-1)
    {
        return TRUE;
    }
    return FALSE;
}

int Trace(int MazeSize, Maze *maze, Pos *TracePos, Stack *History, Stack *CrossPoint)
{
    Pos Buffer;
    int state=0, Cross=0;

    ClonePos(TracePos, &Buffer);
    
    Cross=ChkCross(MazeSize, maze, TracePos);
    
    if( !IsWall(MazeSize, maze, *TracePos, 1, 0) )// Straght
    {   
        state=1;
        Buffer= SetPos(TracePos->x+1, TracePos->y);
    }
    
    else if( !IsWall(MazeSize, maze, *TracePos, 0, 1) )// Down
    {
        state=1;
        Buffer= SetPos(TracePos->x, TracePos->y+1);
    }
    
    else if( !IsWall(MazeSize, maze, *TracePos, 0, -1) )// Up
    {
        state=1;
        Buffer= SetPos(TracePos->x, TracePos->y-1);
    }
    
    else if( !IsWall(MazeSize, maze, *TracePos, -1, 0) )// Back
    {
        state=1;
        Buffer= SetPos(TracePos->x-1, TracePos->y);
    }
    
    if(Cross)
    {
        PushStack(History, *TracePos);
        *(maze+(MazeSize*TracePos->y)+TracePos->x)=1;
        
        PushStack(CrossPoint, *TracePos);
        ClonePos(&Buffer, TracePos);
        
        return CROSS;
    }
    
    if(state)
    {
        PushStack(History, *TracePos);
        *(maze+(MazeSize*TracePos->y)+TracePos->x)=1;
        ClonePos(&Buffer, TracePos);
        
        return TRUE;
    }
    
    return FALSE;
}

int IsWall(int MazeSize, Maze *maze, Pos Now, int Offset_x, int Offset_y)
{
    if(Now.x<MazeSize && Now.y<MazeSize)
    {
        if( ((Now.y+Offset_y<MazeSize && Now.y+Offset_y>=0)
          &&(Now.x+Offset_x<MazeSize && Now.x+Offset_x>=0)) )
        {
            //printf("now: %d, offset: %d\n", Now.x, Offset_x);
            if( *(maze+ ( (Now.y+Offset_y)*MazeSize )+Now.x+Offset_x) )// is wall
            {
                return TRUE;
            }
        }
        
        if( !((Now.y+Offset_y<MazeSize && Now.y+Offset_y>=0)
          &&(Now.x+Offset_x<MazeSize && Now.x+Offset_x>=0)) )
          {
              return TRUE;
          }
    } 
    return FALSE;
}

int ChkCross(int MazeSize, Maze *maze, Pos *NowPos)
{
    int cnt=0;
    
    cnt+=!IsWall(MazeSize, maze, *NowPos, 1, 0);
    //printf("cnt:%d\n", IsWall(MazeSize, maze, *NowPos, -1, 0));
    cnt+=!IsWall(MazeSize, maze, *NowPos, -1, 0);
    //printf("cnt:%d\n", cnt);
    cnt+=!IsWall(MazeSize, maze, *NowPos, 0, 1);
    //printf("cnt:%d\n", cnt);
    cnt+=!IsWall(MazeSize, maze, *NowPos, 0, -1);
    //printf("cnt:%d\n", cnt);
    gotoxy(5, 15);
    //printf("cnt:%d\n", cnt);
    
    if(cnt>1)
    {
        return TRUE;
    }
    return FALSE;
}


void gotoxy(int x, int y)//내가 원하는 위치로 커서 이동
{
    COORD pos = {x, y};//커서가 X좌표에서 -1 한값. Y좌표에서 -1한 값으로 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}
