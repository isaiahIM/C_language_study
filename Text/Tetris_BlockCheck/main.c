#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define RIGHT 100
#define LEFT 97
#define UP 119
#define DOWN 115
#define FALSE 0	
#define TRUE 1

enum Collision
{
	UPCOLLISION=1,
	DOWNCOLLISION,
	RIGHTCOLLISION,
	LEFTCOLLISION
};

typedef struct _POSITION
{
	int X;
	int Y;
} Position;

void Red(void);// 빨간글자 
void ReturnColor(void);// 색 원래대로 

void Gotoxy(int x, int y);
void SetPos(Position *Pos, int x, int y);// 포지션 설정 
void RemovePaint(Position Paint, Position RemoveSize, Position MapSize, unsigned char map[][MapSize.X]);// 페인트 제거 

int Paint(Position Paint, Position PaintSize, Position MapSize, unsigned char map[][MapSize.X]);// 페인팅 
int ChkCollision(Position Paint, Position MapSize, unsigned char map[][MapSize.X]);// 충돌확인 

char ReadKey(void);// 키 입력


int main(int argc, char *argv[]) {
	
	unsigned char map[10][10]={0, };
	unsigned char Mask[4][4];
	
	Position MaskPos;
	Position RemovePos;
	Position MaskSize;
	Position MapSize;
	Position RemoveSize;
	
	int i, j, cnt, CollisionState;
	char dir, First=1;
	
	SetPos(&MaskPos, 0, 0);
	SetPos(&MaskSize, 4, 4);
	SetPos(&MapSize, 10, 10);
	SetPos(&RemovePos, MaskPos.X-2, 0);
	SetPos(&RemoveSize, 4, 4);
	
	for(i=0; i<10; i+=2)
	{	
		map[i][i]=1;
		map[i][i+1]=1;
		map[i+1][i]=1;
		map[i+1][i+1]=1;
	}
	
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			if(map[i][j])
			{
				printf("*");
			}
			else
			{
				printf("-");
			}
		}
		printf("\n");
	}
	
	while(1)
	{
		dir = ReadKey();
		
		CollisionState=ChkCollision(MaskPos, MapSize, map);
		
		if(dir==UP && (CollisionState!=UPCOLLISION))
		{
			SetPos(&MaskPos, MaskPos.X, MaskPos.Y-1);
			SetPos(&RemovePos, MaskPos.X, MaskPos.Y+4);
			SetPos(&RemoveSize, 4, 1);
		}
		
		else if(dir==DOWN && (CollisionState!=DOWNCOLLISION))
		{
			SetPos(&MaskPos, MaskPos.X, MaskPos.Y+1);
			SetPos(&RemovePos, MaskPos.X, MaskPos.Y-1);
			SetPos(&RemoveSize, 4, 1);
		}
		
		else if(dir==RIGHT && (CollisionState!=RIGHTCOLLISION))
		{
			SetPos(&MaskPos, MaskPos.X+1, MaskPos.Y);
			SetPos(&RemovePos, MaskPos.X-1, MaskPos.Y);
			SetPos(&RemoveSize, 1, 4);
		}
		
		else if(dir==LEFT && (CollisionState!=LEFTCOLLISION))
		{
			SetPos(&MaskPos, MaskPos.X-1, MaskPos.Y);
			SetPos(&RemovePos, MaskPos.X+4, MaskPos.Y);
			SetPos(&RemoveSize, 1, 4);
		}
		else
		{
			SetPos(&MaskPos, MaskPos.X, MaskPos.Y);
			SetPos(&RemovePos, RemovePos.X, RemovePos.Y);
			SetPos(&RemoveSize, 0, 0);
		}
		
		if(dir!=FALSE)
		{
		cnt=Paint(MaskPos, MaskSize, MapSize, map);
		
		ReturnColor();
		
		Gotoxy(15, 5);
		printf("%d\n", cnt);
		
		RemovePaint(RemovePos, RemoveSize, MapSize, map);
		}
		
		
		Sleep(100);
	}
	
	return 0;
}

void Red(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void ReturnColor(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void SetPos(Position *Pos, int x, int y)
{
	Pos->X=x;
	Pos->Y=y;
}

void Gotoxy(int x, int y)//내가 원하는 위치로 커서 이동
{
	COORD pos = {x, y};//커서가 X좌표에서 -1 한값. Y좌표에서 -1한 값으로 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void RemovePaint(Position Paint, Position RemoveSize, Position MapSize, unsigned char map[][MapSize.X])
{
	int i, j;
	
	ReturnColor();
	for(i=Paint.Y; i<Paint.Y+RemoveSize.Y; i++)
	{
		for(j=Paint.X; j<Paint.X+RemoveSize.X; j++)
		{	
			Gotoxy(j, i);
			if(map[i][j])
			{
				printf("*");
			}
			else
			{
				printf("-");
			}
		}
	}
}

int Paint(Position Paint, Position PaintSize, Position MapSize, unsigned char map[][MapSize.X])
{
	int i, j, cnt=0;
	Red();// 빨간색 표시
	
	for(i=Paint.Y; i<Paint.Y+PaintSize.Y; i++)
	{
		for(j=Paint.X; j<Paint.X+PaintSize.X; j++)
		{
			Gotoxy(j, i);
			
			if(map[i][j])
			{
				printf("*");
				cnt++;
			}
			
			else
			{
				printf("-");
			}
		}
	}
	ReturnColor();//색깔 원상복귀 	
	return cnt;
}

int ChkCollision(Position Paint, Position MapSize, unsigned char map[][MapSize.X])
{
	if(Paint.X==0)
	{
		return LEFTCOLLISION;
	}
	
	else if(Paint.X+4==MapSize.X)
	{
		return RIGHTCOLLISION;
	}
	
	else if(Paint.Y==0)
	{
		return UPCOLLISION;
	}
	
	else if(Paint.Y+4==MapSize.Y)
	{
		return DOWNCOLLISION;
	}
	
	else
	{
		return FALSE;
	}
}

char ReadKey(void)
{
	if(!kbhit())
	{
		return FALSE;
	}
	
	else
	{
		return getch();
	}
}
