#include <stdio.h>
#include <stdlib.h>

#include "Maze.h"

#define MAZE_SIZE 10

int main(int argc, char *argv[])
{
  Pos TracePos;
  Maze maze[MAZE_SIZE][MAZE_SIZE]=
  {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };
      
      PrtMaze(MAZE_SIZE, *maze, '$');
      
      TracePos=SetPos(0, 2);
      
      while(!IsFinish(TracePos, MAZE_SIZE) )
      {
          PrtTrace(TracePos, '*');
          Trace(MAZE_SIZE, *maze, &TracePos);
          Sleep(100);
      }
      
      PrtTrace(TracePos, '*');
      printf("\n\n\n\n\n\n\n\nFinish!!\n\n");
      
      
  system("PAUSE");	
  return 0;
}
