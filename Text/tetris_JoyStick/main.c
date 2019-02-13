#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MAP_X 10
#define MAP_Y 20
#define RIGHT 100
#define LEFT 97
#define TRUE 1
#define FALSE 0

typedef struct _position
{
	int X;
	int Y;
} Pos;

void PrintMap(int length, int height, char map[][length], Pos blockpos);// 맵 출력 
void InitMap(int map_X, int map_Y, char map[][map_X]);// 맵 초기설정 
void InitDotPos(Pos *dot);// 별 위치 초기회 
void SetDot(Pos *dot, int x, int y);// 별 위치 설정
 
char ReadKey(void);// 키 입력 

int main(int argc, char *argv[]) 
{
	char map[MAP_Y][MAP_X];
	
	int i=1, j, cnt=0, buffer, toggle=1, keybuffer;
	char dir=0;
	
	Pos Dot;// 별 좌표 
	
	InitMap(MAP_X, MAP_Y, map);	// 맵 초기화 
	InitDotPos(&Dot);// 별 위치 초기화 
	
	while(1)
	{
		if(!(i<MAP_Y))
		{
			i=0;
		}
						
		dir=ReadKey();
		
		if(dir==RIGHT)
		{
			cnt+=1;
		}
		
		else if(dir==LEFT)
		{
			cnt-=1;
		}
			
		for(j=0; j<MAP_X; j++)// 맵에 별 추가하는 부분 
		{
			if(j==3)// 사각형 안에서만 별 찍기 
			{
				SetDot(&Dot, j+cnt, i);
				buffer=cnt;
			}
		}
		
		PrintMap(MAP_X, MAP_Y, map, Dot);
		printf("\n\n 왼쪽: a, 오른쪽: d");

		if(toggle%10==0)
		{	
			i++;	
		}
		
		Sleep(100);
		system("cls");
		toggle++;		
	}
	return 0;
}

void PrintMap(int length, int height, char map[][length], Pos blockpos)
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
			
			else if((blockpos.X==j) && (blockpos.Y==i) )// 별 좌표에 왔을때 
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

void InitMap(int map_X, int map_Y, char map[][map_X])
{
	int i, j;
	
	for(i=0; i<map_Y; i++)// 맵 정보 생성 
	{
		for(j=0; j<map_X; j++)
		{
			if(i==0||i==map_Y-1)//천장, 바닥 
			{
				map[i][j]=1;
			}
		
			else if(j==0||j==map_X-1)// 양 끝 
			{
				map[i][j]=1;
			}
			else
			{
				map[i][j]=0;
			}
		}
	}
}

void InitDotPos(Pos *dot)
{
	dot->X=3;
	dot->Y=1;
}

void SetDot(Pos *dot, int x, int y)
{
	dot->X=x;
	dot->Y=y;
}

char ReadKey(void)
{
	if(kbhit())
	{
		return getch(); 
	}
	else
	{
		return FALSE; 
	}
}

