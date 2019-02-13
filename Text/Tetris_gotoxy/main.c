#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define RIGHT 100
#define LEFT 97
#define TRUE 1
#define FALSE 0

enum Collision
{
	DOWNCOLLISION=1,
	RIGHTCOLLISION,
	LEFTCOLLISION
};

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


void InitMap(Size MapSize, char map[][MapSize.Length]);// �� �ʱ⼳�� 
void InitDot(Pos *Dot);// �� ��ġ �ʱ�ȸ 
void ClearCursor(void); // Ŀ�� ����� �Լ� D
void Clear(int *num);// ���� �ʱ�ȭ 

void SetPos(Pos *Pos, int x, int y);// �� ��ġ ����
void Stack(Size MapSize, char map[][MapSize.Length], Pos Dot);// �� �ױ� 
void UpdateMap(Size MapSize, char map[][MapSize.Length], Pos Dot);// �� ��� 
void MoveDot(Pos Dot, Pos RemovePos);// �� ��� 
void gotoxy(int x, int y);// ��ǥ �̵� 

char ReadKey(void);// Ű �Է� 

int ChkCollision(Size MapSize, char map[][MapSize.Length], Pos Dot);// �浹 �˻� (�ϴ�:1, ������:2, ����:3, �浹x:0) 

int main(int argc, char *argv[]) 
{
	ClearCursor();// Ŀ�� ����� 
	
	Pos Dot, Buffer;// �� ��ǥ 
	Size MapSize={10, 20};
	
	char map[MapSize.Height][MapSize.Length];
	
	int i=1, j, cnt=0, toggle=0, CollisionState;
	char dir=0;
	
		
	InitMap(MapSize, map);	// �� �ʱ�ȭ 
	InitDot(&Dot);// �� ��ġ �ʱ�ȭ 
	InitDot(&Buffer);// ���� �ʱ�ȭ 
	
	UpdateMap(MapSize, map, Dot);// �� �ʱ���� 
	
	while(1)
	{	
		CollisionState = ChkCollision(MapSize, map, Dot);// ���� Ȯ��
		
		if( CollisionState == DOWNCOLLISION)// �ϴ� �浹�� �߻��ϸ� 
		{
			Stack(MapSize, map, Dot);// ���� �װ� 
			UpdateMap(MapSize, map, Dot);// ���� ������Ʈ�� 
			Clear(&toggle);	
			i=2;
			Clear(&CollisionState);
			SetPos(&Dot, Dot.X, i);
			continue;	
		}
		
		if(!(i<MapSize.Height))
		{
			i=2;
		}
						
		dir=ReadKey();
		
		if((dir==RIGHT) && (CollisionState!=RIGHTCOLLISION)) 
		{
			cnt=1;
		}
		
		else if((dir==LEFT) && (CollisionState!=LEFTCOLLISION))
		{
			cnt=-1;
		}
		else
		{
			cnt=0;
		}
		
		if(cnt!=0)// ����Ű�� �������� 
		{
			SetPos(&Buffer, Dot.X, Dot.Y);	
		}
		
		if(cnt==0 && Dot.Y!=i)// ����Ű�� ������ �����ٷ� �Ѿ����(Ű�� �ȴ��������� ���۰��� ������Ʈ�� ���ؼ� ����� ���� ����) 
		{
			SetPos(&Buffer, Dot.X, i-1);	
		}
		
		SetPos(&Dot, Dot.X+cnt, i);
		
		Clear(&cnt);
		
		MoveDot(Dot, Buffer);
			
		if(toggle%9==0 )// 1�ʰ� ������ 
		{	
			i++;
			Clear(&toggle);	
		}
		
		Clear(&CollisionState);
		Sleep(100);
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

void InitDot(Pos *Dot)
{
	Dot->X=3;
	Dot->Y=1;
}

void UpdateMap(Size MapSize, char map[][MapSize.Length], Pos Dot)
{
	int i, j;
	system("cls");
	
	for(i=0; i<MapSize.Height; i++)// �� ���� ���� 
	{
		for(j=0; j<MapSize.Length; j++)
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
	
	printf("\n\n ����: a, ������: d");
}

void SetPos(Pos *Pos, int x, int y)
{
	Pos->X=x;
	Pos->Y=y;
}

void Stack(Size MapSize, char map[][MapSize.Length], Pos Dot)
{
	map[Dot.Y][Dot.X]=1;
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

void MoveDot(Pos Dot, Pos RemovePos)
{	
	gotoxy(Dot.X, Dot.Y);
	printf("*");
	
	gotoxy(RemovePos.X, RemovePos.Y);
	printf(" ");
}

void ClearCursor(void)
{
	HANDLE hConsole; // �ܼ� �ڵ�
	CONSOLE_CURSOR_INFO ConsoleCursor; // �ܼ�Ŀ�� ���� ����ü

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �ڵ��� ���ϰ�	
	
	ConsoleCursor.bVisible = FALSE; // true ���� , false �Ⱥ���
	ConsoleCursor.dwSize = 1; // Ŀ�� ������
	
	SetConsoleCursorInfo(hConsole , &ConsoleCursor); // ����
}

void Clear(int *num)
{
	*num=0;
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
	
	else if(map[Dot.Y][Dot.X+1])// ���� �浹 
	{
		return RIGHTCOLLISION;
	}
	
	else if(map[Dot.Y][Dot.X-1])// ���� �浹 
	{
		return LEFTCOLLISION;
	}
	
	return FALSE;
}



