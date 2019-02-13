#include "Maze.h"


void PrtMaze(Size MazeSize, Maze *maze, char Charactor)
{
    int i, j;
    
    for(i=0; i<MazeSize.Height; i++)
    {
        for(j=0; j<MazeSize.Length; j++)
        {
            if( *(maze+(MazeSize.Length*i)+j) )
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

void CloneMaze(Size MazeSize, const Maze *Original, Maze *Clone)
{
    int i, j;
    
    for(i=0; i<MazeSize.Height; i++)
    {
        for(j=0; j<MazeSize.Length; j++)
        {
           *(Clone+(MazeSize.Length*i)+j)= *(Original+(MazeSize.Length*i)+j);
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

int IsFinish(Pos pos, Size MazeSize, Maze *maze, Maze FinishFlag)
{
    if(*(maze+(MazeSize.Length*pos.y)+pos.x)== FinishFlag)
    {
        return TRUE;
    }
    return FALSE;
}

int Trace(Size MazeSize, Maze *maze, Pos *TracePos, Stack *History, Stack *CrossPoint)
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
        *(maze+(MazeSize.Length*TracePos->y)+TracePos->x)=1;
        
        PushStack(CrossPoint, *TracePos);
        ClonePos(&Buffer, TracePos);
        
        return CROSS;
    }
    
    if(state)
    {
        PushStack(History, *TracePos);
        *(maze+(MazeSize.Length*TracePos->y)+TracePos->x)=1;
        ClonePos(&Buffer, TracePos);
        
        return TRUE;
    }
    
    return FALSE;
}

int IsWall(Size MazeSize, Maze *maze, Pos Now, int Offset_x, int Offset_y)
{
    if(Now.x<MazeSize.Length && Now.y<MazeSize.Height)
    {
        if( ((Now.y+Offset_y<MazeSize.Height && Now.y+Offset_y>=0)
          &&(Now.x+Offset_x<MazeSize.Length && Now.x+Offset_x>=0)) )
        {
            //printf("now: %d, offset: %d\n", Now.x, Offset_x);
            if( *(maze+ ( (Now.y+Offset_y)*MazeSize.Length )+Now.x+Offset_x)==1 )// is wall
            {
                return TRUE;
            }
        }
        
        if( !((Now.y+Offset_y<MazeSize.Height && Now.y+Offset_y>=0)
          &&(Now.x+Offset_x<MazeSize.Length && Now.x+Offset_x>=0)) )
          {
              return TRUE;
          }
    } 
    return FALSE;
}

int ChkCross(Size MazeSize, Maze *maze, Pos *NowPos)
{
    int cnt=0;
    
    cnt+=!IsWall(MazeSize, maze, *NowPos, 1, 0);
    cnt+=!IsWall(MazeSize, maze, *NowPos, -1, 0);
    cnt+=!IsWall(MazeSize, maze, *NowPos, 0, 1);
    cnt+=!IsWall(MazeSize, maze, *NowPos, 0, -1);
    
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

Size SetSize(int Length, int Height)
{
    Size size;
    size.Length=Length;
    size.Height=Height;
    
    return size;
}
