#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <graphics.h>

using namespace std;

int main( )
{
	FILE *BmpFile;
	unsigned int *FileData;
	
    BmpFile=fopen("tiger.bmp", "rb");
    
    if(BmpFile==NULL)
    {
        printf("no file!!\n");
        exit(1);
    }
    
    initwindow( 640 , 480 , "WinBGIm" );
	
	
	
    
	outtextxy( 0 ,0 , "Hello WinBGIm!" );
    
	bgiout << "Hello WinBGIm-Stream!" ;
	outstreamxy( 0 , 15 ); 
	
	
	printf( "Hello Console!\n" );

	cout << "Hello Console-Stream!\n" ;
    
    
    
    
	while( !kbhit() ); 
  
    
    
	closegraph( );
    
	return( 0 );
}
