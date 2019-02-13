#include <stdio.h>
#include <stdlib.h>

#include <graphics.h>

#define MAP_X 20
#define MAP_Y 26
#define BLOCK_X 2 
#define BLOCK_X 2
#define BYTE unsigned char
#define RIGHT 100
#define LEFT 97



enum CollisionState
{
    DOWNCOLLISION=1,
    RIGHTCOLLISION,
    LEFTCOLLISION      
};

typedef struct _PIXEL
{
    unsigned int Block_X;
    unsigned int Block_Y;
} Pixel;

typedef struct _SIZE
{
    int Length;
    int Height;
} Size;

typedef struct _POSITION
{
    int X;
    int Y;
} Pos;


void Stack(Size MapSize, BYTE Map[][MAP_X], Pos BlockPos);
void UpdateMap(Size MapSize, char *Block, Pixel pixel, BYTE Map[][MAP_X]);
void Move(Size BlockSize, Pos BlockPos, char *Block, Pixel pixel, BYTE block[][BLOCK_X]);

int ChkCollision(Size MapSize, BYTE Map[][MAP_X], Pos BlockPos, Size BlockSize);

char ReadKey();
Pos SetPos(Pos pos, int x, int y);

Size SetSize(Size size, int Length, int Height);

int main( )
{
    BYTE Map[MAP_Y][MAP_X];
    BYTE Block[2][2]={{1, 1}, {1, 1}};
    unsigned int ImgSize;
	
    char *map;
	char *block;
	char *remove;
    char dir;
    
    int i, j, toggle=0;
    
    Pos BlockPos;
    Pos RemovePos;
    
    Size MapSize;
    Size BlockSize;
    
    Pixel pixel;
    pixel.Block_X=22;
    pixel.Block_Y=22;
    
    MapSize = SetSize(MapSize, MAP_X, MAP_Y);
    BlockSize = SetSize(BlockSize, 2, 2);
    BlockPos = SetPos(BlockPos, 2, 2);
    
       
    for(i=0; i<MapSize.Height; i++)
    {
        for(j=0; j<MapSize.Length; j++)
        {
            if( (i==0) || i==MapSize.Height-1 )
            {
                Map[i][j]=1;
            }
            
            else if( (j==0) || j==MapSize.Length-1 )
            {
                Map[i][j]=1;
            }
            
            else
            {
                Map[i][j]=0;
            }
        }
    }    
    
    initwindow( 448 , 579 , "TetirsStackTest" );
	
	// map information setup
	readimagefile("background.jpg", 0, 0, 448, 579);// imagefile reading
    ImgSize= imagesize(0, 0, 448, 579);// pixel(0,0)~(823,541) of size(1pixel is 4byte)
	map= (char *)malloc(ImgSize);// memory allocation of map size
	getimage(0, 0, 448, 579, map);// image information mapping (0,0) ~ (448, 579) position

    // block information setup
    readimagefile("block1.jpg", 0, 0, 21, 21);
    ImgSize= imagesize(0, 0, 21, 21);
    block= (char *)malloc(ImgSize);
    getimage(0, 0, 21, 21, block);
    
    // removeBlock information setup
    readimagefile("block2.jpg", 0, 0, 21, 21);
    ImgSize= imagesize(0, 0, 21, 21);
    remove= (char *)malloc(ImgSize);
    getimage(0, 0, 21, 21, remove);
    
    
    putimage(0, 0, map, 0);
    UpdateMap(MapSize, block, pixel, Map);
    
    while(1)
    {
          dir=ReadKey();
          if(dir==RIGHT)
          {
              BlockPos = SetPos(BlockPos, BlockPos.X+1, BlockPos.Y);
          }
          putimage(0, 0, map, 0);
          UpdateMap(MapSize, block, pixel, Map);
          Move(BlockSize, BlockPos, block, pixel, Block);
          Sleep(10);
    }     
}

void Stack(Size MapSize, Pos BlockPos, Size BlockSize, BYTE Map[][MAP_X], BYTE Block[][BLOCK_X])
{
	int i, j;
	
	for(i = BlockPos.Y; i < BlockPos.Y+BlockSize.Height; i++)
	{
		for(j = BlockPos.X; j < BlockPos.X+BlockSize.Length; j++)
		{
			if(Block[i-BlockPos.Y][j-BlockPos.X])
			{
				Map[i][j]=Block[i-BlockPos.Y][j-BlockPos.X];
			}
		}
	}
}

void UpdateMap(Size MapSize, char *Block, Pixel pixel, BYTE Map[][MAP_X])
{
    int i, j;
    
    for(i=0; i<MapSize.Height; i++)
    {
        for(j=0; j<MapSize.Length; j++)
        {
            if(Map[i][j])
            {
                putimage(j*(pixel.Block_X), i* (pixel.Block_Y), Block, 0);
            }
        }
    }
}

void Move(Size BlockSize, Pos BlockPos, char *Block, Pixel pixel, BYTE block[][BLOCK_X])
{
	int i, j;
	
	for(i = BlockPos.Y; i < BlockPos.Y  + BlockSize.Height; i++)
	{
		for(j = BlockPos.X; j < BlockPos.X  + BlockSize.Length; j++)
		{
			if(block[i-BlockPos.Y][j-BlockPos.X])
			{
				putimage(j* (pixel.Block_X), i* (pixel.Block_Y), Block, 0);
			}
		}
	}
}


int ChkCollision(Size MzpSize, Pos BlockPos, Size BlockSize, BYTE Map[][MAP_X], BYTE Block[][BLOCK_X])
{
    int down=0, right=0, left=0, i, j;
    
    for(i=BlockPos.Y; i<BlockPos.Y+BlockSize.Height-1; i++)
    {
        for(j=BlockPos.X; j<BlockPos.X+BlockSize.Length-1; j++)
        {
            if(Map[i][j+1] && Block[i-BlockPos.Y][j-BlockPos.X])
            {
                right=1;
            }
                
            if(Map[i][j-1])
            {
                left=1;
            }
                
            if(Map[i+1][j])
            {
                down=1;
            } 
        }
    }
    
    if(down==1)
    return DOWNCOLLISION;
    
    else if(right==1)
    return RIGHTCOLLISION;
    
    else if(left==1)
    return LEFTCOLLISION;
    
    else
    return FALSE;
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

Pos SetPos(Pos pos, int x, int y)
{
    pos.X=x;
    pos.Y=y;
    return pos;
}

Size SetSize(Size size, int Length, int Height)
{
    size.Length=Length;
    size.Height=Height;
    return size;
}
