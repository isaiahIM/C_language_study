#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define RIGHT 100
#define LEFT 97
#define DOWN 115
#define ROTATE 32

#define MAP_X 20
#define MAP_Y 25
#define BLOCKSIZE 4
#define BOOL unsigned char
#define KIND 7
enum COLLISION
{
	DOWNCOLLISION=1,
	RIGHTCOLLISION,
	LEFTCOLLISION
};

typedef struct _POSITION
{
	int X;
	int Y;
} Pos;

typedef struct _SIZE
{
	int Height;
	int Length;
} Size;

typedef struct _BLOCKINFO
{
	Pos BlockPos;
	Size BlockSize;// 블럭크기
	int Kind;
} Block;

void InitMap(Size MapSize, BOOL map[][MapSize.Length]);// 맵 초기화 
void SetBlock(Block *block, Pos BlockPos, Size BlockSize);// 블록 정보 입력 
void UpdateMap(Size MapSize, BOOL map[][MapSize.Length]);// 맵 업데이트

void Stack(Size MapSize, Block BlockInfo, BOOL map[][MapSize.Length], BOOL block[][BlockInfo.BlockSize.Length]);// 블럭쌓기 
void Move(Block BlockInfo, Pos RemovePos, BOOL block[][BlockInfo.BlockSize.Length], BOOL remove[][BlockInfo.BlockSize.Length]);// 블럭 이동 
void RemoveStack(Size MapSize, int RemoveLine, BOOL map[][MapSize.Length]);// 블럭 제거(한줄) 
void RotateArr(Block BlockInfo, BOOL block[][BlockInfo.BlockSize.Length]);// 블럭 회전 
void CloneArr(Block BlockInfo, BOOL Original[][BlockInfo.BlockSize.Length], BOOL Clone[][BlockInfo.BlockSize.Length]);// 배열 복사 함수

void RemoveCursor(void);// 커서 제거 
void Gotoxy(int x, int y);// 좌표 이동함수 

char ReadKey(void);

int ChkStack(Size MapSize, BOOL map[][MapSize.Length]);// 칸이 찼는지 확인 
int ChkCollision(Block BlockInfo, Size MapSize, BOOL map[][MapSize.Length], BOOL block[][BlockInfo.BlockSize.Length]);// 충돌확인
int Random(int Range);

Size SetSize(Size size, int Height, int Length);// 사이즈 정보 입력

Pos SetPos(Pos pos, int x, int y);// 위치 정보 입력 

int main(int argc, char *argv[]) {
	
	RemoveCursor();
	
	BOOL map[MAP_Y][MAP_X];
	BOOL block[KIND][BLOCKSIZE][BLOCKSIZE]=// 원본 블럭 
	{
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 1},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},			
	};
	BOOL remove[BLOCKSIZE][BLOCKSIZE];
	BOOL CloneBlock[BLOCKSIZE][BLOCKSIZE];// 복사할 불럭 
	
	Size MapSize, BlockSize;
	
	Pos BlockPos, RemovePos;
	
	Block BlockInfo;
	
	char dir, CollisionState, DownToggle=1, stack, time=100;
	
	MapSize = SetSize(MapSize, MAP_Y, MAP_X);
	BlockSize = SetSize(BlockSize, BLOCKSIZE, BLOCKSIZE);
	
	BlockPos = SetPos(BlockPos, 3, 2);
	
	SetBlock(&BlockInfo, BlockPos, BlockSize);
	
	InitMap(MapSize, map);
	BlockInfo.Kind=Random(KIND);
	CloneArr(BlockInfo, block[BlockInfo.Kind], CloneBlock);
	while(1)
	{	
		CloneArr(BlockInfo, CloneBlock, remove);
		
		Gotoxy(25, 5);
		printf("a: 오른쪽, d: 왼쪽, s: 하강, 스페이스바: 도형 회전");
		
		time=100;
		
		stack = ChkStack(MapSize, map);		
		if(stack!=0)
		{
			RemoveStack(MapSize, stack, map);
			stack=0;
			
			system("cls");
			UpdateMap(MapSize, map);
		}
		
		RemovePos = SetPos(RemovePos, BlockPos.X, BlockPos.Y);
		dir=ReadKey();

		CollisionState = ChkCollision(BlockInfo, MapSize, map, CloneBlock);
		
		if(CollisionState==DOWNCOLLISION)
		{
			system("cls");
			Stack(MapSize, BlockInfo, map, CloneBlock);
			UpdateMap(MapSize, map);
			
			BlockPos = SetPos(BlockPos, 3, 2);
			
			SetBlock(&BlockInfo, BlockPos, BlockSize);
			BlockInfo.Kind=Random(KIND);
			CloneArr(BlockInfo, block[BlockInfo.Kind], CloneBlock);
			continue;
		}
		
		else if(dir==RIGHT && CollisionState!= RIGHTCOLLISION)
		{
			BlockPos = SetPos(BlockPos, BlockPos.X+1, BlockPos.Y);
		}
		
		else if(dir==LEFT && CollisionState!= LEFTCOLLISION)
		{
			BlockPos = SetPos(BlockPos, BlockPos.X-1, BlockPos.Y);
		}
		
		else if(dir==DOWN && CollisionState!= DOWNCOLLISION)
		{
			time=10;
			BlockPos = SetPos(BlockPos, BlockPos.X, BlockPos.Y+1);
		}
		
		else if(dir==ROTATE && !CollisionState)
		{
			RotateArr(BlockInfo, CloneBlock);
		}
		
		if(DownToggle%10==1)
		{
			DownToggle=1;
			BlockPos = SetPos(BlockPos, BlockPos.X, BlockPos.Y+1);
		}
		
		SetBlock(&BlockInfo, BlockPos, BlockSize);
		
		Move(BlockInfo, RemovePos, CloneBlock, remove);
		Sleep(time);
		CollisionState=FALSE;
		DownToggle++;
	}
	
	return 0;
}

void InitMap(Size MapSize, unsigned char map[][MapSize.Length])
{
	int i, j;
	
	for(i=0; i<MapSize.Height; i++)
	{
		for(j=0; j<MapSize.Length; j++)
		{
			if(i==0 || i==MapSize.Height-1)
			{
				map[i][j]=1;
				printf("*");
			}
			
			else if(j==0 || j==MapSize.Length-1)
			{
				map[i][j]=1;
				printf("*");
			}
			
			else
			{
				map[i][j]=0;
				printf(" ");
			}
		}
		printf("\n");
	}
}

void SetBlock(Block *block, Pos BlockPos, Size BlockSize)
{
	block->BlockPos = SetPos(block->BlockPos, BlockPos.X, BlockPos.Y);
	block->BlockSize = SetSize(block->BlockSize, BlockSize.Height, BlockSize.Length);
}

void Stack(Size MapSize, Block BlockInfo, BOOL map[][MapSize.Length], BOOL block[][BlockInfo.BlockSize.Length])
{
	int i, j;
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y+BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j < BlockInfo.BlockPos.X+BlockInfo.BlockSize.Length; j++)
		{
			if(block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X])
			{
				map[i][j]=1;
			}
		}
	}
	
}

void UpdateMap(Size MapSize, BOOL map[][MapSize.Length])
{
	int i, j;
	for(i=0; i<MapSize.Height; i++)
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
}

void Move(Block BlockInfo, Pos RemovePos, BOOL block[][BlockInfo.BlockSize.Length], BOOL remove[][BlockInfo.BlockSize.Length])
{
	int i, j;
	
	for(i = RemovePos.Y; i < RemovePos.Y + BlockInfo.BlockSize.Height; i++)
	{
		for(j = RemovePos.X; j < RemovePos.X + BlockInfo.BlockSize.Length; j++)
		{
			if(remove[i-RemovePos.Y][j-RemovePos.X]==1)
			{
				Gotoxy(j, i);
				printf(" ");
			}
		}
	}
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y  + BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j < BlockInfo.BlockPos.X  + BlockInfo.BlockSize.Length; j++)
		{
			Gotoxy(j, i);
			if(block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X])
			{
				printf("*");
			}
		}
	}
}

void RemoveStack(Size MapSize, int RemoveLine, BOOL map[][MapSize.Length])
{
	int i, j;
	
	for(i=1; i<MapSize.Length-1; i++)
	{
		map[RemoveLine][i]=0;
	}
	
	for(i=RemoveLine; i>2; i--)
	{
		for(j=1; j<MapSize.Length-1; j++)
		{
			map[i][j]=map[i-1][j];
		}
	}
}

void RotateArr(Block BlockInfo, BOOL block[][BlockInfo.BlockSize.Length])
{
	int i, j, Backup[BlockInfo.BlockSize.Height][BlockInfo.BlockSize.Length];
	
	for(i=0; i<BlockInfo.BlockSize.Height; i++)
	{
		for(j=0; j<BlockInfo.BlockSize.Length; j++)
		{
			Backup[i][j] = block[j][BlockInfo.BlockSize.Length-(i+1)];
		}
	}
	
	for(i=0; i<BlockInfo.BlockSize.Height; i++)
	{
		for(j=0; j<BlockInfo.BlockSize.Length; j++)
		{
			block[i][j] = Backup[i][j];
		}
	}
}

void CloneArr(Block BlockInfo, BOOL Original[][BlockInfo.BlockSize.Length], BOOL Clone[][BlockInfo.BlockSize.Length])
{
	int i, j;
	
	for(i=0; i<BlockInfo.BlockSize.Height; i++)
	{
		for(j=0; j<BlockInfo.BlockSize.Length; j++)
		{
			Clone[i][j]=Original[i][j];
		}
	}
}

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible=0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
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

void Gotoxy(int x, int y)//내가 원하는 위치로 커서 이동
{
	COORD pos = {x, y};//커서가 X좌표에서 -1 한값. Y좌표에서 -1한 값으로 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

int ChkCollision(Block BlockInfo, Size MapSize, BOOL map[][MapSize.Length], BOOL block[][BlockInfo.BlockSize.Length])
{
	int i, j, down=0, right=0, left=0;
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y+BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j <BlockInfo.BlockPos.X+BlockInfo.BlockSize.Length; j++)
		{
			if(map[i+1][j] && block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X])// 하단충돌 
			{
				down=1;
			}
			
			else if(map[i][j+1] && block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X])// 우측충돌 
			{
				right=1;
			}
			
			else if(map[i][j-1] && block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X])// 좌측충돌 
			{
				left=1;
			}
		}
	}
	
	if(down==1)
	{
		return DOWNCOLLISION;
	}
	
	else if(right==1)
	{
		return RIGHTCOLLISION;
	}
	
	else if(left==1)
	{
		return LEFTCOLLISION;
	}
	
	else
	{
		return FALSE;
	}
}

int ChkStack(Size MapSize, BOOL map[][MapSize.Length])
{
	int i, j;
	BOOL Chk;
	for(i=1; i<MapSize.Height-1; i++)
	{
		Chk=1;
		
		for(j=0; j<MapSize.Length; j++)
		{
			Chk = map[i][j]&&Chk;
		}
		
		if(Chk==1)
		{
			return i;
		}
	}
	return FALSE;
}

int Random(int Range)
{
	long seed=time(NULL);
    srand(seed);
    
    return rand()%Range;
}


Size SetSize(Size size, int Height, int Length)
{
	size.Height=Height;
	size.Length=Length;
	return size;
}

Pos SetPos(Pos pos, int x, int y)
{
	pos.X=x;
	pos.Y=y;
	return pos;
}


