#ifndef _MAZE_H
#define _MAZE_H

#include <stdio.h>
#include <Windows.h>

#define MAZE_SIZE 10

#define TRUE 1
#define FALSE 0

typedef struct _POSITION
{
    int x;
    int y;
} Pos;

typedef int Maze;


void gotoxy(int x, int y);

void PrtMaze(int MazeSize, Maze *maze, char Charactor);
void PrtTrace(Pos TracePos, char Trace);

int IsFinish(Pos pos, int MazeSize);
int Trace(int MazeSize, Maze *maze, Pos *TracePos);
int IsWall(int MazeSize, Maze *maze, Pos Now, int Offset_x, int Offset_y);

Pos SetPos(int x, int y);

#endif
