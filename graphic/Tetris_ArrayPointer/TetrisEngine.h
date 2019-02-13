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
	Pos BlockPos;// �� ��ġ 
	Size BlockSize;// ��ũ��
	int Kind;// �� ���� 
	int Delay;// �����ð� 
	int NextBlock;// ������ ����
	int Score;
	int Level;
	int StackCount;
	BYTE GameOver;// ���ӿ��� 
} BLock;

typedef struct _PIXEL
{
    unsigned int Block_X;
    unsigned int Block_Y;
    unsigned int Map_X;
    unsigned int Map_Y;
} Pixel;


void InitMap(Size MapSize, BYTE *map);// �� �ʱ�ȭ  
void InitBlock(BLock *BlockInfo, Size *BlockSize, Pos *BlockPos);// ��� �ʱ�ȭ

void SetBlock(BLock *block, Pos BlockPos, Size BlockSize);// ��� ���� �Է� 
void SetDelay(BLock *BlockInfo, int Time);// �����ð� ���� 
void SetRandom(BLock *BlockInfo, int Range);// ���� ���� 
void SetPixelInfo(Pixel *pixel, unsigned int Block_X, unsigned int Block_Y, unsigned int Map_X, unsigned int Map_Y);
void SetLevel(BLock *BlockInfo, int Level);

void UpdateMap(Size MapSize, char **Block, Pixel pixel, BYTE *Map);// �� ������Ʈ
void Move(BLock BlockInfo, Pos RemovePos, char **Block, char *Remove, Pixel pixel, BYTE *block, BYTE *remove);
void Stack(Size MapSize, BLock BlockInfo, BYTE *map, BYTE *block);// ���ױ� 
void RemoveStack(Size MapSize, int RemoveLine, BYTE *map);// �� ����(����) 
void RotateArr(BLock BlockInfo, BYTE *block);// �� ȸ�� 
void CloneArr(BLock BlockInfo, BYTE *Original, BYTE *Clone);// �迭 ���� �Լ�
void PrtNextBlock(BLock BlockInfo, char **Block, Pixel pixel, BYTE *block);
void SetScore(BLock *BlockIno, int Score);

char ReadKey(void);// Ű �Է�

int IsBGMEnd(void);// bgm func
int ChkStack(Size MapSize, BYTE *map);// ĭ�� á���� Ȯ�� 
int ChkCollision(BLock BlockInfo, Size MapSize, BYTE *map, BYTE *block);// �浹Ȯ��
int Random(int Range);

Size SetSize(Size size, int Height, int Length);// ������ ���� �Է�
Pos SetPos(Pos pos, int x, int y);// ��ġ ���� �Է� 
BYTE ChkGameOver(BLock *BlockInfo, Size MapSize, BYTE *map);// ���ӿ��� ����

#endif
