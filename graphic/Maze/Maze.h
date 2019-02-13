#ifndef _MAZE_H
#define _MAZE_H

#include <stdio.h>
#include <Windows.h>

#include "ListStack.h"

#define CROSS 2

typedef int Maze;
typedef struct _SIZE
{
    int Height;
    int Length;
} Size;

void gotoxy(int x, int y);

void PrtMaze(Size MazeSize, Maze *maze, char Charactor);
void PrtTrace(Pos TracePos, Pos *HistoryPos, char Trace);
void CloneMaze(Size MazeSize, const Maze *Original, Maze *Clone);


int IsFinish(Pos pos, Size MazeSize, Maze *maze, Maze FinishFlag);
int Trace(Size MazeSize, Maze *maze, Pos *TracePos, Stack *History, Stack *CrossPoint);
int IsWall(Size MazeSize, Maze *maze, Pos Now, int Offset_x, int Offset_y);
int ChkCross(Size MazeSize, Maze *maze, Pos *NowPos);

Size SetSize(int Length, int Height);

#endif
