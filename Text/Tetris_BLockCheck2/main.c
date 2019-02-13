#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define RIGHT 100
#define LEFT 97
#define UP 119
#define DOWN 115
#define MAPSIZE 10
#define MASKSIZE 4


enum Collision
{
	UPCOLLISION=1,
	DOWNCOLLISION,
	RIGHTCOLLISION,
	LEFTCOLLISION
};

enum Color// ���� 
{
	DARK,
	DEEP_BLUE,
	DEEP_GREEN,
	DEEP_MINT,
	DEEP_RED,
	DEEP_PUPLE,
	DEEP_YELLOW,
	DEEP_WHITE,
	GRAY,
	BLUE,
	GREEN,
	MINT,
	RED,
	PUPLE,
	YELLOW,
	WHITE
};

typedef struct _INFO
{
	int PosX;
	int PosY;
	int Size_Length;
	int Size_Height;
} Info;

void Color(int color);// ���ڻ� 
void ReturnColor(void);// �� ������� 

void Gotoxy(int x, int y);
void SetInfo(Info *info, int x, int y, int Length, int Height);// ���� ���� 
void RemovePaint(Info RemoveInfo, Info MapInfo, unsigned char map[][MapInfo.Size_Length]);// ����Ʈ ���� 
void PrtMap(Info MapInfo, unsigned char map[][MapInfo.Size_Length]);// �� ��� 
void InitMap(Info MapInfo, unsigned char map[][MapInfo.Size_Length]);// �� �ʱ�ȭ 

int Paint(Info MapInfo, Info MaskInfo, unsigned char map[][MapInfo.Size_Length], unsigned char mask[][MaskInfo.Size_Length]);// ������
int ChkCollision(Info PaintInfo, Info MapInfo, unsigned char map[][MapInfo.Size_Length]);// �浹Ȯ�� 

char ReadKey(void);// Ű �Է�


int main(int argc, char *argv[]) {
	
	int cnt, CollisionState;
	char dir, First=1;
	
	unsigned char map[MAPSIZE][MAPSIZE]={0, };
	unsigned char Mask[MASKSIZE][MASKSIZE]=
	{
		{0, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 1},
		{0, 0, 0, 0}
		
	};
	
	Info MaskInfo;
	Info MapInfo;
	Info RemoveInfo;
	
	SetInfo(&MaskInfo, 0, 0, MASKSIZE, MASKSIZE);
	SetInfo(&MapInfo, 0, 0, MAPSIZE, MAPSIZE);
	SetInfo(&RemoveInfo, -2, 0, MASKSIZE, MASKSIZE);
	
	InitMap(MapInfo, map);
	PrtMap(MapInfo, map);
	
	while(1)
	{
		dir = ReadKey();
		
		CollisionState=ChkCollision(MaskInfo, MapInfo, map);
		
		if(dir==UP && (CollisionState!=UPCOLLISION))
		{	
			SetInfo(&MaskInfo, MaskInfo.PosX, MaskInfo.PosY-1, MaskInfo.Size_Length, MaskInfo.Size_Height);
			SetInfo(&RemoveInfo, MaskInfo.PosX, MaskInfo.PosY+4, 4, 1);
		}
		
		else if(dir==DOWN && (CollisionState!=DOWNCOLLISION))
		{
			SetInfo(&MaskInfo, MaskInfo.PosX, MaskInfo.PosY+1, MaskInfo.Size_Length, MaskInfo.Size_Height);
			SetInfo(&RemoveInfo, MaskInfo.PosX, MaskInfo.PosY-1, 4, 1);
		}
		
		else if(dir==RIGHT && (CollisionState!=RIGHTCOLLISION))
		{
			SetInfo(&MaskInfo, MaskInfo.PosX+1, MaskInfo.PosY, MaskInfo.Size_Length, MaskInfo.Size_Height);
			SetInfo(&RemoveInfo, MaskInfo.PosX-1, MaskInfo.PosY, 1, 4);
		}
		
		else if(dir==LEFT && (CollisionState!=LEFTCOLLISION))
		{
			SetInfo(&MaskInfo, MaskInfo.PosX-1, MaskInfo.PosY, MaskInfo.Size_Length, MaskInfo.Size_Height);
			SetInfo(&RemoveInfo, MaskInfo.PosX+4, MaskInfo.PosY, 1, 4);
		}
		else
		{
			SetInfo(&MaskInfo, MaskInfo.PosX, MaskInfo.PosY, MaskInfo.Size_Length, MaskInfo.Size_Height);
			SetInfo(&RemoveInfo, MaskInfo.PosX, MaskInfo.PosY, 0, 0);
		}
		
		if(dir!=FALSE || First)
		{
			cnt=Paint(MapInfo, MaskInfo, map, Mask);
			
			ReturnColor();
			
			Gotoxy(15, 5);
			printf("%d\n", cnt);
			
			RemovePaint(RemoveInfo, MapInfo, map);
		}
		
		Sleep(100);
		First=0;
	}
	
	return 0;
}


void InitMap(Info MapInfo, unsigned char map[][MapInfo.Size_Length])
{
	int i;
	
	for(i=0; i<10; i+=2)
	{	
		map[i][i]=1;
		map[i][i+1]=1;
		map[i+1][i]=1;
		map[i+1][i+1]=1;
	}
}
void PrtMap(Info MapInfo, unsigned char map[][MapInfo.Size_Length])
{
	int i, j;
	for(i=0; i<MapInfo.Size_Height; i++)
	{
		for(j=0; j<MapInfo.Size_Length; j++)
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
}
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ReturnColor(void)
{
	Color(WHITE);
}

void SetInfo(Info *info, int x, int y, int Length, int Height)
{
	info->PosX=x;
	info->PosY=y;
	info->Size_Height=Height;
	info->Size_Length=Length; 
}

void Gotoxy(int x, int y)//���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
	COORD pos = {x, y};//Ŀ���� X��ǥ���� -1 �Ѱ�. Y��ǥ���� -1�� ������ �̵�
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API �Լ��Դϴ�. �̰� ���ʿ� �����
}

void RemovePaint(Info RemoveInfo, Info MapInfo, unsigned char map[][MapInfo.Size_Length])
{
	int i, j;
	
	ReturnColor();
	for(i=RemoveInfo.PosY; i<RemoveInfo.PosY + RemoveInfo.Size_Height; i++)
	{
		for(j=RemoveInfo.PosX; j<RemoveInfo.PosX + RemoveInfo.Size_Length; j++)
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

int Paint(Info MapInfo, Info MaskInfo, unsigned char map[][MapInfo.Size_Length], unsigned char mask[][MaskInfo.Size_Length])
{
	int i, j, cnt=0, Mask_Y=0, Mask_X=0;
	
	for(i=MaskInfo.PosY; i<MaskInfo.PosY + MaskInfo.Size_Height; i++)
	{
		for(j=MaskInfo.PosX; j<MaskInfo.PosX + MaskInfo.Size_Length; j++)
		{
			Gotoxy(j, i);

			if(map[i][j])
			{
				if(map[i][j]==mask[i-MaskInfo.PosY][j-MaskInfo.PosX])// ����: mask�迭�� ���� mask[0~Paint.Y][0~Paint.X]�� �Ǿ��ϹǷ� i��, j���� for������ �����ߴ� �ʱⰪ�� �� 
				{
					Color(YELLOW);
					printf("*");
					cnt++;
				}
				else
				{
					Color(RED);
					printf("*");
				}
			}
			
			else if(mask[i-MaskInfo.PosY][j-MaskInfo.PosX])
			{
				Color(BLUE);
				printf("*");
			}
			else
			{
				Color(RED);
				printf("-");
			}
		}
	}
	
	ReturnColor();//���� ���󺹱� 	
	return cnt;
}

int ChkCollision(Info PaintInfo, Info MapInfo, unsigned char map[][MapInfo.Size_Length])
{
	if(PaintInfo.PosX==0)
	{
		return LEFTCOLLISION;
	}
	
	else if(PaintInfo.PosX+4==MapInfo.Size_Length)
	{
		return RIGHTCOLLISION;
	}
	
	else if(PaintInfo.PosY==0)
	{
		return UPCOLLISION;
	}
	
	else if(PaintInfo.PosY+4==MapInfo.Size_Height)
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
