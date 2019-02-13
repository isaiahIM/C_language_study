#include <graphics.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#include "TetrisEngine.h"

void InitMap(Size MapSize, BYTE *map)
{
	int i ,j;
	
	for(i=0; i<MapSize.Height; i++)
	{
		for(j=0; j<MapSize.Length; j++)
		{
			if(i==0 || i==MapSize.Height-1)
			{
				*(map+((i*MapSize.Length)+j) )=8;
			}
			
			else if(j==0 || j==MapSize.Length-1)
			{
				*(map+((i*MapSize.Length)+j) )=8;
			}
			
			else
			{
				*(map+((i*MapSize.Length)+j) )=0;
			}
            //printf("%d", *(map+((i*MapSize.Length)+j)) );		
		}
		//printf("\n");
	}
}

void InitBlock(BLock *BlockInfo, Size *BlockSize, Pos *BlockPos)
{
	*BlockSize = SetSize(*BlockSize, BLOCKSIZE, BLOCKSIZE);
	*BlockPos = SetPos(*BlockPos, 5, 1);
	
	BlockInfo->Kind = Random(KIND);
	Sleep(1000);
	BlockInfo->NextBlock = Random(KIND);
	BlockInfo->Score=0;
	BlockInfo->BlockPos = SetPos(BlockInfo->BlockPos, BlockPos->X, BlockPos->X);
	BlockInfo->BlockSize = SetSize(BlockInfo->BlockSize, BlockSize->Height, BlockSize->Length);
	BlockInfo->Delay=100;
	BlockInfo->GameOver=FALSE;
	BlockInfo->Level=1;
	BlockInfo->StackCount=0;
}

void SetBlock(BLock *block, Pos BlockPos, Size BlockSize)
{
	block->BlockPos = SetPos(block->BlockPos, BlockPos.X, BlockPos.Y);
	block->BlockSize = SetSize(block->BlockSize, BlockSize.Height, BlockSize.Length);
}

void SetDelay(BLock *BlockInfo, int Time)
{
	BlockInfo->Delay=Time;
}

void SetRandom(BLock *BlockInfo, int Range)
{
	BlockInfo->Kind = BlockInfo->NextBlock;
	BlockInfo->NextBlock=Random(Range);
}

void SetPixelInfo(Pixel *pixel, unsigned int Block_X, unsigned int Block_Y, unsigned int Map_X, unsigned int Map_Y)
{   
    pixel->Block_X=Block_X;
    pixel->Block_Y=Block_Y;
    pixel->Map_X=Map_X;
    pixel->Map_Y=Map_Y;
}

void UpdateMap(Size MapSize, char **Block, Pixel pixel, BYTE *Map)
{
    int i, j, kind;
    char *block;
    
    
    for(i=0; i<MapSize.Height; i++)
    {
        for(j=0; j<MapSize.Length; j++)
        {
            if( *(Map+((i*MapSize.Length)+j)) )
            {
                kind= *(Map+((i*MapSize.Length)+j) )-1;
                block= *(Block+kind);
                putimage(j*(pixel.Block_X+GAP+2)+3, i* (pixel.Block_Y+GAP)+2, block, 0);
            }
             printf("%d", *(Map+((i*MapSize.Length)+j) ));
        }
        printf("\n");
    }
    printf("\n\n\n");
    
}

void Stack(Size MapSize, BLock BlockInfo, BYTE *map, BYTE *block)
{
	int i, j;
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y+BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j < BlockInfo.BlockPos.X+BlockInfo.BlockSize.Length; j++)
		{   
            if( *(block+( ((i-BlockInfo.BlockPos.Y)*BlockInfo.BlockSize.Height))+(j-BlockInfo.BlockPos.X)) )
			{
				*(map+((i*MapSize.Length)+j) )= *(block+( ((i-BlockInfo.BlockPos.Y)*BlockInfo.BlockSize.Height))+(j-BlockInfo.BlockPos.X));
			}
		}
	}
}

void Move(BLock BlockInfo, Pos RemovePos, char **Block, char *Remove, Pixel pixel, BYTE *block, BYTE *remove)
{
	int i, j, kind, page=0;
	char *blocks;
	
    setactivepage(page);
    for(i = RemovePos.Y; i < RemovePos.Y + BlockInfo.BlockSize.Height; i++)
	{
		for(j = RemovePos.X; j < RemovePos.X + BlockInfo.BlockSize.Length; j++)
		{
            if( *(remove+( ((i-RemovePos.Y)*BlockInfo.BlockSize.Height))+(j-RemovePos.X)) )
			{
                putimage(j*(pixel.Block_X+GAP+2)+3, i* (pixel.Block_Y+GAP)+2, Remove, 0);
			}
		}
	}
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y  + BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j < BlockInfo.BlockPos.X  + BlockInfo.BlockSize.Length; j++)
		{
			
            if( *(block+( ( (i-BlockInfo.BlockPos.Y)*BlockInfo.BlockSize.Height))+(j- BlockInfo.BlockPos.X) ) )
			{
                kind = *(block+( ((i-BlockInfo.BlockPos.Y)*BlockInfo.BlockSize.Height))+(j- BlockInfo.BlockPos.X) )-1;
                blocks=*(Block+kind);
				putimage(j*(pixel.Block_X+GAP+2)+3, i*(pixel.Block_Y+GAP)+2, blocks, 0);
			}
		}
	}
	setvisualpage(page);
	page++;
	page%=2;
}

void RemoveStack(Size MapSize, int RemoveLine, BYTE *map)
{
	int i, j;
	
	for(i=1; i<MapSize.Length-1; i++)
	{   
        *(map+(RemoveLine*MapSize.Length)+i)=0;
	}
	
	for(i=RemoveLine; i>2; i--)
	{
		for(j=1; j<MapSize.Length-1; j++)
		{
			*(map+(i*MapSize.Length)+j)= *(map+((i-1)*MapSize.Length)+j);
		}
	}
}

void RotateArr(BLock BlockInfo, BYTE *block)
{
	int i, j; 
    BYTE Backup[BlockInfo.BlockSize.Height][BlockInfo.BlockSize.Length];
	
	for(i=0; i<BlockInfo.BlockSize.Height; i++)
	{
		for(j=0; j<BlockInfo.BlockSize.Length; j++)
		{   
            Backup[i][j] = *(block+(j*BlockInfo.BlockSize.Height)+(BlockInfo.BlockSize.Length-(i+1)) );
		}
	}
	
	for(i=0; i<BlockInfo.BlockSize.Height; i++)
	{
		for(j=0; j<BlockInfo.BlockSize.Length; j++)
		{
			*(block+(i*BlockInfo.BlockSize.Height)+j) = Backup[i][j];
		}
	}
}

void CloneArr(BLock BlockInfo, BYTE *Original, BYTE *Clone)
{
	int i, j;
	
	for(i=0; i<BlockInfo.BlockSize.Height; i++)
	{
		for(j=0; j<BlockInfo.BlockSize.Length; j++)
		{
            *(Clone+(i*BlockInfo.BlockSize.Height)+j)= *(Original+(i*BlockInfo.BlockSize.Height)+j);
		}
	}
}

void PrtNextBlock(BLock BlockInfo, char **Block, Pixel pixel, BYTE *block)
{
    int i, j;
    
    for(i=0; i<BlockInfo.BlockSize.Height; i++)
    {
        for(j=0; j<BlockInfo.BlockSize.Length; j++)
        {
            if( *(block+(i*BlockInfo.BlockSize.Height)+j) )
            {
                putimage( (pixel.Map_X + 30) + (j* (pixel.Block_X)+5), 30+(i* (pixel.Block_Y+5) ), Block[*(block+(i*BlockInfo.BlockSize.Height)+j)-1], 0);
            }
        }
    }
}

void SetScore(BLock *BlockInfo, int Score)
{
    BlockInfo->Score=Score;
}

void SetLevel(BLock *BlockInfo, int Level)
{
    BlockInfo->Level=Level;
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

int ChkCollision(BLock BlockInfo, Size MapSize, BYTE *map, BYTE *block)
{
	int i, j;
	int Down=0, Right=0, Left=0;
	
	for(i = BlockInfo.BlockPos.Y; i < BlockInfo.BlockPos.Y+BlockInfo.BlockSize.Height; i++)
	{
		for(j = BlockInfo.BlockPos.X; j <BlockInfo.BlockPos.X+BlockInfo.BlockSize.Length; j++)
		{
			
            if( *(map+(((i+1)*MapSize.Length)+j) ) 
               && *(block+( (i-BlockInfo.BlockPos.Y)*BlockInfo.BlockSize.Height)+(j-BlockInfo.BlockPos.X)) )// 하단충돌 
			{
                Down=1;
			}
			
			else if( *(map+((i*MapSize.Length)+j+1) ) 
                    && *(block+( (i-BlockInfo.BlockPos.Y)*BlockInfo.BlockSize.Height)+(j-BlockInfo.BlockPos.X)) )// 우측충돌 
			{
				Right=1;
			}
			
			else if( *(map+((i*MapSize.Length)+j-1) ) 
                    && *(block+( (i-BlockInfo.BlockPos.Y)*BlockInfo.BlockSize.Height)+(j-BlockInfo.BlockPos.X)) )// 좌측충돌 
			{
				Left=1;
			}
		}
	}
	
    if(Down)
	{
        return DOWNCOLLISION;
    }
    
    else if(Right)
	{
        return RIGHTCOLLISION;
    }
    
    else if(Left)
	{
        return LEFTCOLLISION;
    }
	
	return FALSE;
}

int ChkStack(Size MapSize, BYTE *map)
{
	int i, j;
	BYTE Chk;
	for(i=1; i<MapSize.Height-1; i++)
	{
		Chk=1;
		
		for(j=0; j<MapSize.Length; j++)
		{
			Chk = ( *(map+(i*MapSize.Length)+j) )&&Chk;
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

BYTE ChkGameOver(BLock *BlockInfo, Size MapSize, BYTE *map)
{
	int i;
	
	for(i=1; i<MapSize.Length-1; i++)
	{
		if( *(map+(2*MapSize.Length)+i) )
		{
			BlockInfo->GameOver=TRUE;
			return TRUE;
		}
	}
	return FALSE;
}


