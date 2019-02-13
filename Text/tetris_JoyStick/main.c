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

void PrintMap(int length, int height, char map[][length], Pos blockpos);// �� ��� 
void InitMap(int map_X, int map_Y, char map[][map_X]);// �� �ʱ⼳�� 
void InitDotPos(Pos *dot);// �� ��ġ �ʱ�ȸ 
void SetDot(Pos *dot, int x, int y);// �� ��ġ ����
 
char ReadKey(void);// Ű �Է� 

int main(int argc, char *argv[]) 
{
	char map[MAP_Y][MAP_X];
	
	int i=1, j, cnt=0, buffer, toggle=1, keybuffer;
	char dir=0;
	
	Pos Dot;// �� ��ǥ 
	
	InitMap(MAP_X, MAP_Y, map);	// �� �ʱ�ȭ 
	InitDotPos(&Dot);// �� ��ġ �ʱ�ȭ 
	
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
			
		for(j=0; j<MAP_X; j++)// �ʿ� �� �߰��ϴ� �κ� 
		{
			if(j==3)// �簢�� �ȿ����� �� ��� 
			{
				SetDot(&Dot, j+cnt, i);
				buffer=cnt;
			}
		}
		
		PrintMap(MAP_X, MAP_Y, map, Dot);
		printf("\n\n ����: a, ������: d");

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
	
	for(i=0; i<height; i++)// �� ���� ���� 
	{
		for(j=0; j<length; j++)
		{
			if(map[i][j])
			{
				printf("*");
			}
			
			else if((blockpos.X==j) && (blockpos.Y==i) )// �� ��ǥ�� ������ 
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
	
	for(i=0; i<map_Y; i++)// �� ���� ���� 
	{
		for(j=0; j<map_X; j++)
		{
			if(i==0||i==map_Y-1)//õ��, �ٴ� 
			{
				map[i][j]=1;
			}
		
			else if(j==0||j==map_X-1)// �� �� 
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

