#ifndef _MYGRAPHIC_H

#define _MYGRAPHIC_H

#include <graphics.h>

typedef struct _POS
{
    int x;
    int y;
} Pos;

typedef struct _SIZE
{
    int Length;
    int Height;
} Size;


void ClearArr(char *arr);

int ChkClickImg(Pos ClickPos, Pos ImgPos, Size ImgSize);// clck image checking function

Pos GetClick(void);
Pos SetPos(Pos pos, int x, int y);

Size SetSize(Size size, int Length, int Height);
#endif
