#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <math.h>

#define PI 3.14159
#define SQUARE_SIZE 150

typedef struct _POSITION
{
    int x;
    int y;
} Pos;

void SetPos(Pos *pos, int x, int y);
void Sqare(int square[], Pos StartPos, int r, float Degree);

float ToRadian(float Degree);

int main( )
{
	initwindow( 700 , 500 , "WinBGIm" );
	
    int r=SQUARE_SIZE, first=0, second=30-first, third=60-first, flag;
    int sqare[10];
	Pos StartPos;
	
	SetPos(&StartPos, 300, 200);
     
    while(1)
	{    
         if(r==SQUARE_SIZE)
         {
             flag=-1;
         }
         
         if(r==0)
         {
             flag=1;
         }
         
         cleardevice();// clear screen
         
         Sqare(sqare, StartPos, r, first);
         drawpoly(5,sqare);
         
         Sqare(sqare, StartPos, r, second);
         drawpoly(5,sqare);
         
         Sqare(sqare, StartPos, r, third);
         drawpoly(5,sqare);
         
         first+=1;
         second+=1;
         third+=1;
         r+=flag;
         
         Sleep(1); 
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

void Sqare(int square[], Pos StartPos, int r, float Degree)
{
    Pos pos;
    float degree=Degree-90;
    int i;
 
    for(i=0; i<10; i+=2)
    {
        degree+=90;
        Degree=ToRadian(degree);
        SetPos(&pos, StartPos.x + (int)(r*(cos(Degree))), StartPos.y + (int)(r*(sin(Degree))));
        square[i]=pos.x;
        square[i+1]=pos.y;
        line(StartPos.x, StartPos.y, square[i], square[i+1]);
    } 
}

float ToRadian(float Degree)
{
    return (Degree*PI)/180;
}
