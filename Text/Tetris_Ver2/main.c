#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define BYTE unsigned char
#define RIGHT 100
#define LEFT 97
#define DOWN 115
#define ROTATE 32
#define MAP_X 15
#define MAP_Y 20
#define BLOCKSIZE 4
#define KIND 7
#define PRTPOS 2 

enum COLLISION
{
	DOWNCOLLISION=1,
	RIGHTCOLLISION,
	LEFTCOLLISION
};

enum Color// 색깔 
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
	Pos BlockPos;// 블럭 위치 
	Size BlockSize;// 블럭크기
	int Kind;// 블럭 종류 
	int Delay;// 지연시간 
	int NextBlock;// 다음블럭 종류
	BYTE GameOver;// 게임오버 
} Block;

void InitMap(Size MapSize, BYTE map[][MapSize.Length]);// 맵 초기화  
void InitBlock(Block *BlockInfo, Size *BlockSize, Pos *BlockPos);// 블록 초기화
void SetBlock(Block *block, Pos BlockPos, Size BlockSize);// 블록 정보 입력 
void SetDelay(Block *BlockInfo, int Time);// 지연시간 설정 
void SetRandom(Block *BlockInfo, int Range);// 랜덤 설정 
void UpdateMap(Size MapSize, BYTE map[][MapSize.Length]);// 맵 업데이트
void Color(int color);// 색깔 
void ReturnColor(void);// 색깔 되돌리기 

void Move(Block BlockInfo, Pos RemovePos, BYTE block[][BlockInfo.BlockSize.Length], BYTE remove[][BlockInfo.BlockSize.Length]);// 블럭 이동 
void Stack(Size MapSize, Block BlockInfo, BYTE map[][MapSize.Length], BYTE block[][BlockInfo.BlockSize.Length]);// 블럭쌓기 
void RemoveStack(Size MapSize, int RemoveLine, BYTE map[][MapSize.Length]);// 블럭 제거(한줄) 
void RotateArr(Block BlockInfo, BYTE block[][BlockInfo.BlockSize.Length]);// 블럭 회전 
void CloneArr(Block BlockInfo, BYTE Original[][BlockInfo.BlockSize.Length], BYTE Clone[][BlockInfo.BlockSize.Length]);// 배열 복사 함수
void PrtNextBlock(Block BlockInfo, BYTE block[][BlockInfo.BlockSize.Length], Pos PrtPos);// 다음 블럭 출럭

void RemoveCursor(void);// 커서 제거 
void Gotoxy(int x, int y);// 좌표 이동함수  

char ReadKey(void);// 키 입력

int ChkStack(Size MapSize, BYTE map[][MapSize.Length]);// 칸이 찼는지 확인 
int ChkCollision(Block BlockInfo, Size MapSize, BYTE map[][MapSize.Length], BYTE block[][BlockInfo.BlockSize.Length]);// 충돌확인
int Random(int Range);

Size SetSize(Size size, int Height, int Length);// 사이즈 정보 입력
Pos SetPos(Pos pos, int x, int y);// 위치 정보 입력 
BYTE ChkGameOver(Block *BlockInfo, Size MapSize, BYTE map[][MapSize.Length]);// 게임오버 유무

int main(int argc, char *argv[]) {
	
	RemoveCursor();
	
	BYTE map[MAP_Y][MAP_X];
	BYTE block[KIND][BLOCKSIZE][BLOCKSIZE]=// 원본 블럭 
	{
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{15, 15, 15, 15},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 14, 0, 0},
			{0, 14, 14, 14},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 13},
			{0, 13, 13, 13},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 12, 12, 0},
			{0, 12, 12, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 11, 11, 0},
			{11, 11, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 10, 0, 0},
			{10, 10, 10, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{9, 9, 0, 0},
			{0, 9, 9, 0},
			{0, 0, 0, 0}
		},			
	};

	BYTE remove[BLOCKSIZE][BLOCKSIZE];// 삭제할 블럭 
	BYTE CloneBlock[BLOCKSIZE][BLOCKSIZE];// 복사할 불럭 
	
	Size MapSize, BlockSize;
	
	Pos BlockPos, RemovePos, PrtPos;
	
	Block BlockInfo;
	
	char dir, CollisionState, DownToggle=1, stack;
	
	MapSize = SetSize(MapSize, MAP_Y, MAP_X);
	
	PrtPos = SetPos(PrtPos, 25, 7);
	
	InitMap(MapSize, map);
	InitBlock(&BlockInfo, &BlockSize, &BlockPos);
	
	CloneArr(BlockInfo, block[BlockInfo.Kind], CloneBlock);
	RemoveCursor();
	
	while(1)
	{
		SetDelay(&BlockInfo, 100);
		
		if(ChkGameOver(&BlockInfo, MapSize, map))
		{
			break;
		}
		
		Gotoxy(50, 5);
		printf("a: 오른쪽, d: 왼쪽, s: 하강, 스페이스바: 도형 회전");
		PrtNextBlock(BlockInfo, block[BlockInfo.NextBlock], PrtPos);
		
		RemovePos = SetPos(RemovePos, BlockPos.X, BlockPos.Y);
		CloneArr(BlockInfo, CloneBlock, remove);
	
		stack = ChkStack(MapSize, map);
		if(stack!=0)
		{
			RemoveStack(MapSize, stack, map);
			stack=0;
			
			system("cls");
			UpdateMap(MapSize, map);
		}
		
		
		dir=ReadKey();

		CollisionState = ChkCollision(BlockInfo, MapSize, map, CloneBlock);
		
		if(CollisionState==DOWNCOLLISION)
		{
			system("cls");
			
			Stack(MapSize, BlockInfo, map, CloneBlock);
			UpdateMap(MapSize, map);
			
			BlockPos = SetPos(BlockPos, 3, 1);
			SetBlock(&BlockInfo, BlockPos, BlockSize);
			SetRandom(&BlockInfo, KIND);
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
			SetDelay(&BlockInfo, 10);
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
		Sleep(BlockInfo.Delay);
		
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
				map[i][j]=6;
			}
			
			else if(j==0 || j==MapSize.Length-1)
			{
				map[i][j]=6;
			}
			
			else
			{
				map[i][j]=0;
			}
			if(map[i][j])
			{
				Color(map[i][j]);
				printf("■");
				ReturnColor();
			}
			else
			{
				printf("  ");
			}
			
		}
		printf("\n");
	}
}

void InitBlock(Block *BlockInfo, Size *BlockSize, Pos *BlockPos)
{
	*BlockSize = SetSize(*BlockSize, BLOCKSIZE, BLOCKSIZE);
	*BlockPos = SetPos(*BlockPos, 3, 1);
	
	BlockInfo->Kind = Random(KIND);
	Sleep(1000);
	BlockInfo->NextBlock = Random(KIND);
	
	BlockInfo->BlockPos = SetPos(BlockInfo->BlockPos, BlockPos->X, BlockPos->X);
	BlockInfo->BlockSize = SetSize(BlockInfo->BlockSize, BlockSize->Height, BlockSize->Length);
	BlockInfo->Delay=100;
	BlockInfo->GameOver=FALSE;
}

void SetBlock(Block *block, Pos BlockPos, Size BlockSize)
{
	block->BlockPos = SetPos(block->BlockPos, BlockPos.X, BlockPos.Y);
	block->BlockSize = SetSize(block->BlockSize, BlockSize.Height, BlockSize.Length);
	block->Delay=100;
}

void SetDelay(Block *BlockInfo, int Time)
{
	BlockInfo->Delay=Time;
}

void SetRandom(Block *BlockInfo, int Range)
{
	BlockInfo->Kind = BlockInfo->NextBlock;
	BlockInfo->NextBlock=Random(Range);
}

void UpdateMap(Size MapSize, BYTE map[][MapSize.Length])
{
	int i, j;
	for(i=0; i<MapSize.Height; i++)
	{
		for(j=0; j<MapSize.Length; j++)
		{
			if(map[i][j])
			{
				Color(map[i][j]);
				printf("■");
				ReturnColor();
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
}

void Stack(Size MapSize, Block BlockInfo, BYTE map[][MapSize.Length], BYTE block[][BlockInfo.BlockSize.Length])
{
	int i, j;
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y+BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j < BlockInfo.BlockPos.X+BlockInfo.BlockSize.Length; j++)
		{
			if(block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X])
			{
				map[i][j]=block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X];
			}
		}
	}
}

void Move(Block BlockInfo, Pos RemovePos, BYTE block[][BlockInfo.BlockSize.Length], BYTE remove[][BlockInfo.BlockSize.Length])
{
	int i, j;
	
	for(i = RemovePos.Y; i < RemovePos.Y + BlockInfo.BlockSize.Height; i++)
	{
		for(j = RemovePos.X; j < RemovePos.X + BlockInfo.BlockSize.Length; j++)
		{
			if(remove[i-RemovePos.Y][j-RemovePos.X])
			{
				Gotoxy(j*PRTPOS, i);
				printf("  ");
			}
		}
	}
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y  + BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j < BlockInfo.BlockPos.X  + BlockInfo.BlockSize.Length; j++)
		{	
			if(block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X])
			{
				Gotoxy(10, 25);
				Gotoxy(j*PRTPOS, i);
				Color(block[i-BlockInfo.BlockPos.Y][j-BlockInfo.BlockPos.X]);
				printf("■");
				ReturnColor();
			}
		}
	}
	
}

void RemoveStack(Size MapSize, int RemoveLine, BYTE map[][MapSize.Length])
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

void RotateArr(Block BlockInfo, BYTE block[][BlockInfo.BlockSize.Length])
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

void CloneArr(Block BlockInfo, BYTE Original[][BlockInfo.BlockSize.Length], BYTE Clone[][BlockInfo.BlockSize.Length])
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

void PrtNextBlock(Block BlockInfo, BYTE block[][BlockInfo.BlockSize.Length], Pos PrtPos)
{
	int i, j;
	
	Gotoxy(PrtPos.X*2, PrtPos.Y);
	printf("100%% 안§심§놀이터♣ 혁♥진♥이♥의 테※트※리※스※");
	Gotoxy(PrtPos.X*2, PrtPos.Y+2);
	printf(" ☆다음블럭☆");
	
	for(i=PrtPos.Y+3; i< PrtPos.Y+3+BlockInfo.BlockSize.Height; i++)
	{
		for(j=PrtPos.X+5; j< PrtPos.X+5+BlockInfo.BlockSize.Length; j++)
		{
			Gotoxy(j*PRTPOS, i);
			
			if(block[i-PrtPos.Y-3][j-PrtPos.X-5])
			{
				Color(block[i-PrtPos.Y-3][j-PrtPos.X-5]);
				printf("■");
				ReturnColor();
			}
			else
			{
				printf("  ");
			}
		}
	}
}

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
//	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible=0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void Gotoxy(int x, int y)//내가 원하는 위치로 커서 이동
{
	COORD pos = {x, y};//커서가 X좌표에서 -1 한값. Y좌표에서 -1한 값으로 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ReturnColor(void)
{
	Color(WHITE);
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

int ChkCollision(Block BlockInfo, Size MapSize, BYTE map[][MapSize.Length], BYTE block[][BlockInfo.BlockSize.Length])
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

int ChkStack(Size MapSize, BYTE map[][MapSize.Length])
{
	int i, j;
	BYTE Chk;
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

BYTE ChkGameOver(Block *BlockInfo, Size MapSize, BYTE map[][MapSize.Length])
{
	int i;
	
	for(i=1; i<MapSize.Length-1; i++)
	{
		if(map[3][i])
		{
			Gotoxy(MapSize.Length/2, MapSize.Height/2);
			printf("G\t A\t M\t E");
			Gotoxy(MapSize.Length/2, (MapSize.Height/2)+3);
			printf("O\t V\t E\t R\n\n\n\n\n\n\n\n\n\n\n\n");
			BlockInfo->GameOver=TRUE;
			return TRUE;
		}
	}
	return FALSE;
}
