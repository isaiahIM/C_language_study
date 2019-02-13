#ifndef TETRIS_ENGINE_H
#define TETIRS_ENGINE_H

#define BYTE unsigned char
#define BLOCKSIZE 4
#define KIND 7
#define GAP 3
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
	Pos BlockPos;// 블럭 위치 
	Size BlockSize;// 블럭크기
	int Kind;// 블럭 종류 
	int Delay;// 지연시간 
	int NextBlock;// 다음블럭 종류
	int Score;
	int Level;
	int StackCount;
	BYTE GameOver;// 게임오버 
} BLock;

typedef struct _PIXEL
{
    unsigned int Block_X;
    unsigned int Block_Y;
    unsigned int Map_X;
    unsigned int Map_Y;
} Pixel;


void InitMap(Size MapSize, BYTE *map);// 맵 초기화  
void InitBlock(BLock *BlockInfo, Size *BlockSize, Pos *BlockPos);// 블록 초기화

void SetBlock(BLock *block, Pos BlockPos, Size BlockSize);// 블록 정보 입력 
void SetDelay(BLock *BlockInfo, int Time);// 지연시간 설정 
void SetRandom(BLock *BlockInfo, int Range);// 랜덤 설정 
void SetPixelInfo(Pixel *pixel, unsigned int Block_X, unsigned int Block_Y, unsigned int Map_X, unsigned int Map_Y);
void SetLevel(BLock *BlockInfo, int Level);

void UpdateMap(Size MapSize, char **Block, Pixel pixel, BYTE *Map);// 맵 업데이트
void Move(BLock BlockInfo, Pos RemovePos, char **Block, char *Remove, Pixel pixel, BYTE *block, BYTE *remove);
void Stack(Size MapSize, BLock BlockInfo, BYTE *map, BYTE *block);// 블럭쌓기 
void RemoveStack(Size MapSize, int RemoveLine, BYTE *map);// 블럭 제거(한줄) 
void RotateArr(BLock BlockInfo, BYTE *block);// 블럭 회전 
void CloneArr(BLock BlockInfo, BYTE *Original, BYTE *Clone);// 배열 복사 함수
void PrtNextBlock(BLock BlockInfo, char **Block, Pixel pixel, BYTE *block);
void SetScore(BLock *BlockIno, int Score);

char ReadKey(void);// 키 입력

int IsBGMEnd(void);// bgm func
int ChkStack(Size MapSize, BYTE *map);// 칸이 찼는지 확인 
int ChkCollision(BLock BlockInfo, Size MapSize, BYTE *map, BYTE *block);// 충돌확인
int Random(int Range);

Size SetSize(Size size, int Height, int Length);// 사이즈 정보 입력
Pos SetPos(Pos pos, int x, int y);// 위치 정보 입력 
BYTE ChkGameOver(BLock *BlockInfo, Size MapSize, BYTE *map);// 게임오버 유무

#endif
