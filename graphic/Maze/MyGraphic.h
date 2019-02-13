#ifndef _MY_GRAPHIC_H
#define _MY_GRAPHIC_H

#include <graphics.h>
#include <stdlib.h>

#include "Maze.h"

typedef struct _IMAGE_POSITION 
{
    int x;
    int y;
} ImgPos;

typedef struct _IMAGE_SIZE
{
    int Height;
    int Length;
} ImgSize;

void SetImgInfo(char *ImgName, ImgSize size, char **Img);
void DisplayImg(ImgPos pos, char *Img);

void DisplayMaze_Graphic(Size MazeSize, Maze *maze, int GapSize, char *Img_Wall, char *Img_Empty);
void DisplayTrace_Graphic(Pos TracePos, Pos *HistoryPos, char *Img_Tracer, char *Img_BackGround, int GapSize);

ImgSize SetImgSize(int Length, int Height);
ImgPos SetImgPos(int x, int y);
ImgPos ConvImgPos(Pos *pos, int GapSize);

#endif
