#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MAP_X 10
#define MAP_Y 20
#define RIGHT 100
#define LEFT 97
#define BOOL unsigned int
#define TRUE 1
#define FALSE 0

void PrintMap(int length, int height, char map[][length]);// 맵 출력 
BOOL Collision(int pos1, int pos2);// 충돌 확인 
//void Gotoxy(int x, int y);

int main(int argc, char *argv[]) {
	char map[MAP_Y][MAP_X];
	int i=1, j, cnt=0;
	char dir=0;
	
	for(i=0; i<MAP_Y; i++)// 맵 정보 생성 
	{
		for(j=0; j<MAP_X; j++)
		{
			if(i==0||i==MAP_Y-1)//천장, 바닥 
			{
				map[i][j]=1;
			}
		
			else if(j==0||j==MAP_X-1)// 양 끝 
			{
					map[i][j]=1;
			}
			else
			{
				map[i][j]=0;
			}
		}
	}
	
	
	while(1)
	{
		
		
		for(i=1; i<MAP_Y; i++)
		{
			PrintMap(MAP_X, MAP_Y, map);
			for(j=0; j<MAP_X; j++)
			{
				if(i>1)//이전에 찍었던 별 지우기 
				{
					map[i-1][3]=0;
				}
				
				if(j==3)// 사각형 안에서만 별 찍기 
				{
					map[i][j]=1;
				}
			}
			Sleep(1000);
			system("cls");
		}
			
		
	}
	
	return 0;
}

void PrintMap(int length, int height, char map[][length])
{
	int i, j;
	
	for(i=0; i<height; i++)// 맵 정보 생성 
	{
		for(j=0; j<length; j++)
		{
			if(map[i][j])
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}


//void Gotoxy(int x, int y)
//{
//	COORD pos={x-1, y};
//
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}

//void ClearPos(int x, int y)
//{
//	Gotoxy(x, y);
//	printf(" ");	
//}
