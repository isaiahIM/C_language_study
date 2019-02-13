#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <math.h>

#define PI 3.14159

typedef struct _POSITION
{
    int x;
    int y;
} Pos;

void SetPos(Pos *pos, int x, int y);

float ToRadian(float Degree);

int main( )
{
	initwindow( 700 , 500 , "WinBGIm" );
	
    int r=100, up=0, down=180-up, right=90-up, left=270-up, flag;
    float Degree;
	Pos StartPos, EndPos;
	
	SetPos(&StartPos, 300, 200);
	
    while(1)
	{    if(r==0)
         {
             flag=1;
         }
         else if(r==100)
         {
             flag=-1;
         }
             
         up++;
         down++;
         right++;
         left++;
         cleardevice();// clear screen
         Degree = ToRadian(up);// degree to radian(sin(), cos() angle used to radian)
         SetPos(&EndPos, StartPos.x + (int)(r*(cos(Degree))), StartPos.y + (int)(r*(sin(Degree))));
         line(StartPos.x, StartPos.y, EndPos.x, EndPos.y);
             
         Degree = ToRadian(down);
         SetPos(&EndPos, StartPos.x + (int)(r*(cos(Degree))), StartPos.y + (int)(r*(sin(Degree))));
         line(StartPos.x, StartPos.y, EndPos.x, EndPos.y);
         
         Degree = ToRadian(right);
         SetPos(&EndPos, StartPos.x + (int)(r*(cos(Degree))), StartPos.y + (int)(r*(sin(Degree))));
         line(StartPos.x, StartPos.y, EndPos.x, EndPos.y);
         
         Degree = ToRadian(left);
         SetPos(&EndPos, StartPos.x + (int)(r*(cos(Degree))), StartPos.y + (int)(r*(sin(Degree))));
         line(StartPos.x, StartPos.y, EndPos.x, EndPos.y);
         Sleep(1);
         
         r+=flag;  
    }
    getch();
	closegraph( );
    
	return( 0 );
}

void SetPos(Pos *pos, int x, int y)
{
    pos->x=x;
    pos->y=y;     
}

float ToRadian(float Degree)
{
    return (Degree*PI)/180;
}
