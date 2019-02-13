#include <stdio.h>
#include <iostream>
#include <time.h>

#include "MyGraphic.h"
#include "Maze.h"

#define MAZE_SIZE_X 33
#define MAZE_SIZE_Y 25
#define IMG_COUNT 5
#define BLOCK_SIZE 20

int main( )
{
	initwindow( 660 , 500 , "maze" );
	
    int i;
    char *Img[IMG_COUNT];
    
	char *ImgName[IMG_COUNT]=
	{
        "background.jpg",
        "background.jpg",
        "brick.jpg",
        "finish.jpg",
        "steve.jpg"
    };
    
    Size MazeSize;
    
	ImgSize imgSize[IMG_COUNT];
	ImgPos imgPos[IMG_COUNT];
	
	MazeSize= SetSize(MAZE_SIZE_X, MAZE_SIZE_Y);
    
    imgSize[0]= SetImgSize(660 , 500);// background
	imgSize[1]= SetImgSize(BLOCK_SIZE, BLOCK_SIZE);// null block
	imgSize[2]= SetImgSize(BLOCK_SIZE, BLOCK_SIZE);// brick
	imgSize[3]= SetImgSize(250, 150);// finish
	imgSize[4]= SetImgSize(BLOCK_SIZE, BLOCK_SIZE);// steve
	
	imgPos[0]= SetImgPos(0, 0);
	imgPos[1]= SetImgPos(0, 0);
	imgPos[2]= SetImgPos(0, 0);
	imgPos[3]= SetImgPos(100, 100);
	imgPos[4]= SetImgPos(0, 0);
	
	for(i=0; i<IMG_COUNT; i++)
	{
        SetImgInfo(ImgName[i], imgSize[i], &Img[i]);
    }
 
  int TraceState, delay;
  
  clock_t TraceStartTime,  TraceFinishTime, ShortestStartTime, ShortestEndTime;// timer value
  float SearchTime, Delay, ShortestTime;// convert time to float value and print value
  
  Pos TracePos;
  Stack CrossPoint, History, ShortestDist;
  
  InitStack(&CrossPoint);
  InitStack(&History);
  InitStack(&ShortestDist);
  
  Maze Original[MAZE_SIZE_Y][MAZE_SIZE_X]=
  {     
{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1},
{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},
{1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1},
{1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1},
{1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1},
{1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1},
{1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	0,	1},
{1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1},
{1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1},
{1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1},
{1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1},
{1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},
{1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1},
{1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1},
{1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1},
{1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1},
{1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1},
{1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1},
{1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	0,	1},
{1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1},
{1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1},
{1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	2,	1,	0,	1},
{1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	1,	1,	0,	1},
{1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1},
{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1}
	};
	
  Maze Clone[MAZE_SIZE_Y][MAZE_SIZE_X];

    CloneMaze(MazeSize, *Original, *Clone);
    PrtMaze(MazeSize, *Original, '$');
    
    DisplayMaze_Graphic(MazeSize, *Original, BLOCK_SIZE, Img[2], Img[1]);
    
    TracePos=SetPos(1, 1);
    
    delay=50;
    
    TraceStartTime=clock();
    while(!IsFinish(TracePos, MazeSize, *Clone, 2) )
      {
          PushStack(&ShortestDist, TracePos);
          TraceState= Trace(MazeSize, *Clone, &TracePos, &History, &CrossPoint);
          
          if( TraceState ==FALSE)
          {
              DisplayTrace_Graphic(TracePos, &TracePos, Img[4], Img[1], BLOCK_SIZE);
              PrtTrace(TracePos, &TracePos, '*');
              
              while( !CompPos(PeekStack(&ShortestDist), PeekStack(&CrossPoint)) )
              {
                  ClonePos(PeekStack(&ShortestDist), &TracePos);
                  DisplayTrace_Graphic(TracePos, PeekStack(&History), Img[4], Img[1], BLOCK_SIZE);
                  
                  PushStack(&History, *PeekStack(&ShortestDist));
                  ClonePos(&TracePos, PeekStack(&ShortestDist));
                  
                  PopStack(&ShortestDist);
                  Sleep(10);
              }
              ClonePos(PeekStack(&CrossPoint), &TracePos);
              PopStack(&CrossPoint);
          }
          
          DisplayTrace_Graphic(TracePos, PeekStack(&History), Img[4], Img[1], BLOCK_SIZE);
          PrtTrace(TracePos, PeekStack(&History), '*');
          Sleep(delay);
      }
      TraceFinishTime=clock();
      
      SearchTime= (float)(TraceFinishTime-TraceStartTime)/CLOCKS_PER_SEC;
      Delay=(float)delay/1000;
      
      PrtTrace(TracePos, PeekStack(&History), '*');
      
      DisplayImg(imgPos[3], Img[3]);
      
      printf("\n\n\n\n\n\n\n\n\n\n\nSearch Finish!!\n\n");
      Sleep(5000);
      
      
      ShortestStartTime=clock();
      TracePos=SetPos(1, 1);
      LFirst(&ShortestDist);
      
      ClonePos(GetNow(&ShortestDist), &TracePos);
      DisplayImg(ConvImgPos(GetNow(&ShortestDist), BLOCK_SIZE), Img[4]);
      Sleep(delay);
          
      while(LNext(&ShortestDist) )
      {   
          ClonePos(GetNow(&ShortestDist), &TracePos);
          DisplayImg(ConvImgPos(GetNow(&ShortestDist), BLOCK_SIZE), Img[4]);
          Sleep(delay);
      }
      ShortestEndTime=clock();
      ShortestTime= (float)(ShortestEndTime-ShortestStartTime)/CLOCKS_PER_SEC;
      
      printf("Move Delay: %f Second\n\n", Delay);
      printf("Search Count: %d\t", GetCount(&History));
      printf("Shortest Distance Count: %d\n\n", GetCount(&ShortestDist));
      printf("Search time: %f second\t", SearchTime);
      printf("Shortest time: %f second\n", ShortestTime);
          
	while( !kbhit() ); 
  
    
    
	closegraph( );
    system("PAUSE");	
	
    return( 0 );
}
