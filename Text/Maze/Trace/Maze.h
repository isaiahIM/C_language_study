#ifndef _MAZE_H
#define _MAZE_H

#include <stdio.h>
#include <Windows.h>

#include "ListStack.h"

#define CROSS 2
typedef int Maze;


void gotoxy(int x, int y);

void PrtMaze(int MazeSize, Maze *maze, char Charactor);
void PrtTrace(Pos TracePos, Pos *HistoryPos, char Trace);
void CloneMaze(int MazeSize, const Maze *Original, Maze *Clone);

int IsFinish(Pos pos, int MazeSize);
int Trace(int MazeSize, Maze *maze, Pos *TracePos, Stack *History, Stack *CrossPoint);
int IsWall(int MazeSize, Maze *maze, Pos Now, int Offset_x, int Offset_y);
int ChkCross(int MazeSize, Maze *maze, Pos *NowPos);


#endif
