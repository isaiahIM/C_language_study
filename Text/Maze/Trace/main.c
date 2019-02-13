#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Maze.h"

#define MAZE_SIZE 15
/*
void PrtMaze(int MazeSize, Maze *maze, char Charactor);
void PrtTrace(Pos TracePos, Pos *HistoryPos, char Trace);
void CloneMaze(int MazeSize, const Maze *Original, Maze *Clone);

int IsFinish(Pos pos, int MazeSize);
int Trace(int MazeSize, Maze *maze, Pos *TracePos, Stack *History, Stack *CrossPoint);
int IsWall(int MazeSize, Maze *maze, Pos Now, int Offset_x, int Offset_y);



void InitStack(Stack *stack);
void ClonePos(const Pos *Original, Pos *Clone);
void PrtPos(Pos *pos);

int IsEmpty(Stack *stack);
int GetCount(Stack *stack);

Pos *PushStack(Stack *stack, Pos pos);
Pos *PeekStack(Stack *stack);
Pos *PopStack(Stack *stack);
Pos SetPos(int x, int y);
*/
int main(int argc, char *argv[])
{
  int TraceState, delay;
  
  clock_t MazeStartTime,  MazeFinishTime;// timer value
  float SearchTime, Delay;// convert time to float value and print value
  
  Pos TracePos;
  Stack CrossPoint, History;
  
  InitStack(&CrossPoint);
  InitStack(&History);
  
  Maze Original[MAZE_SIZE][MAZE_SIZE]=
  {     { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,1,0,0,0,0,0,0,1 },
		{ 1,0,1,0,1,1,0,0,0,1,1,0,1,1,1 },
		{ 1,0,1,0,0,0,1,0,1,0,1,0,0,0,1 },
		{ 1,0,1,1,1,0,1,0,1,0,1,1,1,0,1 },
		{ 1,0,1,0,1,0,1,0,0,0,1,0,0,0,1 },
		{ 1,0,1,0,0,0,1,1,1,1,1,0,1,0,1 },
		{ 1,0,1,1,1,1,0,0,0,1,0,0,1,0,1 },
		{ 1,0,0,1,0,0,0,1,0,0,1,1,0,0,1 },
		{ 1,1,0,1,0,1,0,0,1,0,0,0,0,1,1 },
		{ 1,1,0,0,1,1,1,0,1,1,1,1,1,1,1 },
		{ 1,0,1,0,0,0,1,0,0,1,0,0,0,0,1 },
		{ 1,0,1,0,1,0,1,1,0,0,0,1,1,0,0 },
		{ 1,0,0,0,1,0,0,0,1,1,0,0,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};
  Maze Clone[MAZE_SIZE][MAZE_SIZE];

    CloneMaze(MAZE_SIZE, *Original, *Clone);
    PrtMaze(MAZE_SIZE, *Original, '$');
    TracePos=SetPos(1, 7);
    
    delay=100;
    
    MazeStartTime=clock();
    while(!IsFinish(TracePos, MAZE_SIZE) )
      {
          TraceState= Trace(MAZE_SIZE, *Clone, &TracePos, &History, &CrossPoint);
          
          if( TraceState ==FALSE)
          {
              PrtTrace(TracePos, &TracePos, '*');
              ClonePos(PeekStack(&CrossPoint), &TracePos);
              PopStack(&CrossPoint);
          }
          
          PrtTrace(TracePos, PeekStack(&History), '*');
          Sleep(delay);
      }
      MazeFinishTime=clock();
      
      SearchTime= (float)(MazeFinishTime-MazeStartTime)/CLOCKS_PER_SEC;
      Delay=(float)delay/1000;
      
      PrtTrace(TracePos, PeekStack(&History), '*');
      
      printf("\n\n\n\n\n\n\n\n\n\n\nFinish!!\n\n");
      printf("Move Delay: %f Second\n", Delay);
      printf("Move Count: %d\n", GetCount(&History));
      printf("Search time: %f second\n", SearchTime);
    
  system("PAUSE");	
  return 0;
}
