#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define RIGHT 100
#define LEFT 97
#define TRUE 1
#define FALSE 0
#define DOWNCOLLISION 1
#define RIGHTCOLLISION 2
#define LEFTCOLLISION 3

typedef struct _position
{
	int X;
	int Y;
} Pos;

typedef struct _size
{
	int Length;// ���� 
	int Height;// ���� 
} Size;

void PrintMap(Size MapSize, char map[][MapSize.Length], Pos Dot);// �� ��� 
void InitMap(Size MapSize, char map[][MapSize.Length]);// �� �ʱ⼳�� 
void InitDot(Pos *Dot);// �� ��ġ �ʱ�ȸ 
void SetDot(Pos *Dot, int x, int y);// �� ��ġ ����
void Stack(Size MapSize, char map[][MapSize.Length], Pos Dot);// �� �ױ� 

char ReadKey(void);// Ű �Է� 
int ChkCollision(Size MapSize, char map[][MapSize.Length], Pos Dot);// �浹 �˻� (�ϴ�:1, ��:2, �浹x:0) 

int main(int argc, char *argv[]) 
{
	// Ŀ�� ����� �κ� 
	HANDLE hConsole; // �ܼ� �ڵ�
	CONSOLE_CURSOR_INFO ConsoleCursor; // �ܼ�Ŀ�� ���� ����ü

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �ڵ��� ���ϰ�	
	
	ConsoleCursor.bVisible = FALSE; // true ���� , false �Ⱥ���
	ConsoleCursor.dwSize = 1; // Ŀ�� ������
	
	SetConsoleCursorInfo(hConsole , &ConsoleCursor); // ����
	// Ŀ�� ����� �κ�
	
	Pos Dot;// �� ��ǥ 
	Size MapSize={10, 20};
	
	char map[MapSize.Height][MapSize.Length];
	
	int i=1, j, cnt=0, buffer, toggle=1, CollisionState;
	char dir=0;
	
		
	InitMap(MapSize, map);	// �� �ʱ�ȭ 
	InitDot(&Dot);// �� ��ġ �ʱ�ȭ 
	
	while(1)
	{	
		CollisionState = ChkCollision(MapSize, map, Dot);
		
		if( CollisionState == DOWNCOLLISION)// �ϴ� �浹�� �߻��ϸ� 
		{
			Stack(MapSize, map, Dot);
		}
		
		if(!(i<MapSize.Height+1))
		{
			i=1;
		}
						
		dir=ReadKey();
		
		if((dir==RIGHT) && (CollisionState!=RIGHTCOLLISION))
		{
			cnt+=1;
		}
		
		else if((dir==LEFT) && (CollisionState!=LEFTCOLLISION))
		{
			cnt-=1;
		}
			
		for(j=0; j<MapSize.Length; j++)// �ʿ� �� �߰��ϴ� �κ� 
		{
			if(j==3)// �簢�� �ȿ����� �� ��� 
			{
				SetDot(&Dot, j+cnt, i);
				buffer=cnt;
			}
		}
		
		PrintMap(MapSize, map, Dot);
		printf("\n\n ����: a, ������: d");

		if(toggle%10==0 || CollisionState==DOWNCOLLISION)
		{	
			i++;
			toggle=0;	
		}
		
		Sleep(100);
		system("cls");
		toggle++;		
	}
	return 0;
}


void InitMap(Size MapSize, char map[][MapSize.Length])
{
	int i, j;
	
	for(i=0; i<MapSize.Height; i++)// �� ���� ���� 
	{
		for(j=0; j<MapSize.Length; j++)
		{
			if(i==0||i==MapSize.Height-1)//õ��, �ٴ� 
			{
				map[i][j]=1;
			}
		
			else if(j==0||j==MapSize.Length-1)// �� �� 
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

void PrintMap(Size MapSize, char map[][MapSize.Length], Pos Dot)
{
	int i, j;
	
	for(i=0; i<MapSize.Height; i++)// �� ���� ���� 
	{
		for(j=0; j<MapSize.Length; j++)
		{
			if(map[i][j])
			{
				printf("*");
			}
			
			else if((Dot.X==j) && (Dot.Y==i) )// �� ��ǥ�� ������ 
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

void InitDot(Pos *Dot)
{
	Dot->X=3;
	Dot->Y=2;
}

void SetDot(Pos *Dot, int x, int y)
{
	Dot->X=x;
	Dot->Y=y;
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

int ChkCollision(Size MapSize, char map[][MapSize.Length], Pos Dot)
{
	if(map[Dot.Y+1][Dot.X])// �ϴ� �浹 
	{
		return DOWNCOLLISION;
	}
	
	if(map[Dot.Y][Dot.X+1])// ���� �浹 
	{
		return RIGHTCOLLISION;
	}
	
	if(map[Dot.Y][Dot.X-1])// ���� �浹 
	{
		return LEFTCOLLISION;
	}
	
	return FALSE;
}

void Stack(Size MapSize, char map[][MapSize.Length], Pos Dot)
{
	map[Dot.Y][Dot.X]=1;
}
