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
	int Length;// 가로 
	int Height;// 세로 
} Size;


void InitMap(Size MapSize, char map[][MapSize.Length]);// 맵 초기설정 
void InitDot(Pos *Dot);// 별 위치 초기회 
void ClearCursor(void); // 커서 지우는 함수 D
void Clear(int *num);// 변수 초기화 

void SetPos(Pos *Pos, int x, int y);// 별 위치 설정
void Stack(Size MapSize, char map[][MapSize.Length], Pos Dot);// 블럭 쌓기 
void UpdateMap(Size MapSize, char map[][MapSize.Length], Pos Dot);// 맵 출력 
void MoveDot(Pos Dot, Pos RemovePos);// 별 출력 
void gotoxy(int x, int y);// 좌표 이동 

char ReadKey(void);// 키 입력 

int ChkCollision(Size MapSize, char map[][MapSize.Length], Pos Dot);// 충돌 검사 (하단:1, 오른쪽:2, 왼쪽:3, 충돌x:0) 

int main(int argc, char *argv[]) 
{
	ClearCursor();// 커서 지우기 
	
	Pos Dot, Buffer;// 별 좌표 
	Size MapSize={10, 20};
	
	char map[MapSize.Height][MapSize.Length];
	
	int i=1, j, cnt=0, toggle=0, CollisionState;
	char dir=0;
	
		
	InitMap(MapSize, map);	// 맵 초기화 
	InitDot(&Dot);// 별 위치 초기화 
	InitDot(&Buffer);// 버퍼 초기화 
	
	UpdateMap(MapSize, map, Dot);// 맵 초기출력 
	
	while(1)
	{	
		CollisionState = ChkCollision(MapSize, map, Dot);// 퉁돌 확인
		
		if( CollisionState == DOWNCOLLISION)// 하단 충돌이 발생하면 
		{
			Stack(MapSize, map, Dot);// 별을 쌓고 
			UpdateMap(MapSize, map, Dot);// 맵을 업데이트함 
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
		
		if(cnt!=0)// 방향키가 눌렸을때 
		{
			SetPos(&Buffer, Dot.X, Dot.Y);	
		}
		
		if(cnt==0 && Dot.Y!=i)// 방향키가 눌리고 다음줄로 넘어갔을때(키가 안눌렸을때는 버퍼값을 업데이트를 안해서 생기는 오류 방지) 
		{
			SetPos(&Buffer, Dot.X, i-1);	
		}
		
		SetPos(&Dot, Dot.X+cnt, i);
		
		Clear(&cnt);
		
		MoveDot(Dot, Buffer);
			
		if(toggle%9==0 )// 1초가 지나면 
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

void InitDot(Pos *Dot)
{
	Dot->X=3;
	Dot->Y=1;
}

void UpdateMap(Size MapSize, char map[][MapSize.Length], Pos Dot)
{
	int i, j;
	system("cls");
	
	for(i=0; i<MapSize.Height; i++)// 맵 정보 생성 
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
	
	printf("\n\n 왼쪽: a, 오른쪽: d");
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
	HANDLE hConsole; // 콘솔 핸들
	CONSOLE_CURSOR_INFO ConsoleCursor; // 콘솔커서 정보 구조체

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 핸들을 구하고	
	
	ConsoleCursor.bVisible = FALSE; // true 보임 , false 안보임
	ConsoleCursor.dwSize = 1; // 커서 사이즈
	
	SetConsoleCursorInfo(hConsole , &ConsoleCursor); // 설정
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
	if(map[Dot.Y+1][Dot.X])// 하단 충돌 
	{
		return DOWNCOLLISION;
	}
	
	else if(map[Dot.Y][Dot.X+1])// 우측 충돌 
	{
		return RIGHTCOLLISION;
	}
	
	else if(map[Dot.Y][Dot.X-1])// 좌측 충돌 
	{
		return LEFTCOLLISION;
	}
	
	return FALSE;
}



