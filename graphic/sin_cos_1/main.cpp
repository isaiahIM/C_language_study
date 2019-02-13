#include <stdio.h>
#include <iostream>
#include <math.h>
#include <graphics.h>

#define PI 3.14159 
using namespace std;

typedef struct _POSITION
{
    int x, y;
} Pos;

void SetPos(Pos *pos, int x, int y);

int main( )
{
    Pos Start, Last;
    
    int r=100, i;
    float Degree;
    
    SetPos(&Start, 300, 300);
	initwindow( 640 , 480 , "WinBGIm" );


 while(1)
 {
    for(i=360; i>=180; i--)
    {
       cleardevice();// clear screen
       Degree=(PI*i)/180;// degree to radian(sin(), cos() angle used to radian)
       SetPos(&Last, Start.x + (int)(r*(cos(Degree))), Start.y + (int)(r*(sin(Degree))));
        line(Start.x, Start.y, Last.x, Last.y);
       Sleep(1);
    }
    
    for(i=180; i<=360; i++)
    {
       cleardevice();
       Degree=(PI*i)/180;
       SetPos(&Last, Start.x + (int)(r*(cos(Degree))), Start.y + (int)(r*(sin(Degree))));
       line(Start.x, Start.y, Last.x, Last.y);
       Sleep(1);  
    }         
 }
	getch();
	closegraph( );
    
	return( 0 );
}

void SetPos(Pos *pos, int  x, int y)
{
    pos->x= x;
    pos->y= y;
}
