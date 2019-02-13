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
	int Length;// 가로 
	int Height;// 세로 
} Size;

void PrintMap(Size MapSize, char map[][MapSize.Length], Pos Dot);// 맵 출력 
void InitMap(Size MapSize, char map[][MapSize.Length]);// 맵 초기설정 
void InitDot(Pos *Dot);// 별 위치 초기회 
void SetDot(Pos *Dot, int x, int y);// 별 위치 설정
void Stack(Size MapSize, char map[][MapSize.Length], Pos Dot);// 블럭 쌓기 

char ReadKey(void);// 키 입력 
int ChkCollision(Size MapSize, char map[][MapSize.Length], Pos Dot);// 충돌 검사 (하단:1, 벽:2, 충돌x:0) 

int main(int argc, char *argv[]) 
{
	// 커서 숨기는 부분 
	HANDLE hConsole; // 콘솔 핸들
	CONSOLE_CURSOR_INFO ConsoleCursor; // 콘솔커서 정보 구조체

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 핸들을 구하고	
	
	ConsoleCursor.bVisible = FALSE; // true 보임 , false 안보임
	ConsoleCursor.dwSize = 1; // 커서 사이즈
	
	SetConsoleCursorInfo(hConsole , &ConsoleCursor); // 설정
	// 커서 숨기는 부분
	
	Pos Dot;// 별 좌표 
	Size MapSize={10, 20};
	
	char map[MapSize.Height][MapSize.Length];
	
	int i=1, j, cnt=0, buffer, toggle=1, CollisionState;
	char dir=0;
	
		
	InitMap(MapSize, map);	// 맵 초기화 
	InitDot(&Dot);// 별 위치 초기화 
	
	while(1)
	{	
		CollisionState = ChkCollision(MapSize, map, Dot);
		
		if( CollisionState == DOWNCOLLISION)// 하단 충돌이 발생하면 
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
			
		for(j=0; j<MapSize.Length; j++)// 맵에 별 추가하는 부분 
		{
			if(j==3)// 사각형 안에서만 별 찍기 
			{
				SetDot(&Dot, j+cnt, i);
				buffer=cnt;
			}
		}
		
		PrintMap(MapSize, map, Dot);
		printf("\n\n 왼쪽: a, 오른쪽: d");

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
	
	for(i=0; i<MapSize.Height; i++)// 맵 정보 생성 
	{
		for(j=0; j<MapSize.Length; j++)
		{
			if(i==0||i==MapSize.Height-1)//천장, 바닥 
			{
				map[i][j]=1;
			}
		
			else if(j==0||j==MapSize.Length-1)// 양 끝 
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
	
	for(i=0; i<MapSize.Height; i++)// 맵 정보 생성 
	{
		for(j=0; j<MapSize.Length; j++)
		{
			if(map[i][j])
			{
				printf("*");
			}
			
			else if((Dot.X==j) && (Dot.Y==i) )// 별 좌표에 왔을때 
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
	if(map[Dot.Y+1][Dot.X])// 하단 충돌 
	{
		return DOWNCOLLISION;
	}
	
	if(map[Dot.Y][Dot.X+1])// 우측 충돌 
	{
		return RIGHTCOLLISION;
	}
	
	if(map[Dot.Y][Dot.X-1])// 좌측 충돌 
	{
		return LEFTCOLLISION;
	}
	
	return FALSE;
}

void Stack(Size MapSize, char map[][MapSize.Length], Pos Dot)
{
	map[Dot.Y][Dot.X]=1;
}
