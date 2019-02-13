#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>

#define MAP_X 15
#define MAP_Y 20

void Map(int length, int height);
void Gotoxy(int x, int y);
void ClearPos(int x, int y);

int main(int argc, char *argv[]) {
	
	int i;
	Map(MAP_X, MAP_Y);
	while(1)
	{
		for(i=0; i<MAP_Y-1; i++)
		{
			Gotoxy(5, i+1);
			printf("*");
			
			if(i>0)
			{
				ClearPos(5, i);
			}
		
			Sleep(300);
		}
	}
	
	return 0;
}

void Map(int length, int height)
{
	int i, j;
	for(i=0; i<height; i++)
	{
		for(j=0; j<length; j++)
		{
			if(i==0||i==height-1)
			{
				printf("*");	
			}
			
			else
			{
				if(j==0||j==length-1)
				{
					printf("*");	
				}
				else
				{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}

void Gotoxy(int x, int y)
{
	COORD pos={x-1, y};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ClearPos(int x, int y)
{
	Gotoxy(x, y);
	printf(" ");	
}
