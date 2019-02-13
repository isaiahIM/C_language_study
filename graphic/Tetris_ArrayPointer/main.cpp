#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>
#include <conio.h>

#include "digitalv.h"
#include "TetrisEngine.h"


#define RIGHT 0x4d
#define LEFT 0x4b
#define DOWN 0x50
#define SPACE 32
#define ROTATE 0x48

#define MAP_X 10
#define MAP_Y 20

#define BLOCKSIZE 4
#define KIND 7
#define COLOR 8
#define GAP 3

//windows API MCI struct
//MCI Open Parameters struct
MCI_OPEN_PARMS m_mciOpenParms;
//MCI Play Parameters struct
MCI_PLAY_PARMS m_mciPlayParms;
//MCI Status Parameters sturct
MCI_STATUS_PARMS m_mciStatusParms;

//Device ID variable
DWORD m_dwDeviceID;


int main(int argc, char *argv[]) {
    
     
     //BackGruond Music play
	//MCI Open element & Device type setting
	m_mciOpenParms.lpstrElementName = "tetris_background_music.wav"; // same directory File path
    m_mciOpenParms.lpstrDeviceType = "waveaudio";

	//set MCI Open
    //mciSen/*ommandA(NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,(DWORD)(LPVOID)&m_mciOpenParms);
	mciSendCommandA(0, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,(DWORD)(LPVOID)&m_mciOpenParms);

	//get MCI device ID
	m_dwDeviceID = m_mciOpenParms.wDeviceID;

	//Send command : wave file play & repeat setting
	mciSendCommandA(m_dwDeviceID, MCI_PLAY, MCI_NOTIFY|MCI_DGV_PLAY_REPEAT,(DWORD)(LPVOID)&m_mciPlayParms);
    
	char *Block[COLOR];
	char *Remove, *gameOver, *lose, *Map, *Next, *Score, *Level, *Help;

	char Pscore[10], level[3];
    unsigned int ImgSize;
    
    Pixel pixel;
    SetPixelInfo(&pixel, 19, 19, 244, 444);
	
	initwindow( pixel.Map_X+245, pixel.Map_Y, "Tetris_bgm" );

    // block information setup
    readimagefile("block1.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[0]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[0]);
    
    readimagefile("block4.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[1]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[1]);
    
    readimagefile("block5.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[2]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[2]);
    
    readimagefile("block7.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[3]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[3]);
    
    readimagefile("block2.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[4]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[4]);
    
    readimagefile("block3.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[5]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[5]);
    
    readimagefile("block6.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[6]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[6]);
    
    readimagefile("block8.jpg", 0, 0, pixel.Block_X, pixel.Block_Y);
    ImgSize= imagesize(0, 0, pixel.Block_X, pixel.Block_Y);
    Block[7]= (char *)malloc(ImgSize);
    getimage(0, 0,pixel.Block_X, pixel.Block_Y, Block[7]);
    
    // removeBlock information setup
    readimagefile("Empty_block.jpg", 0, 0, 21, 21);
    ImgSize= imagesize(0, 0, 21, 21);
    Remove= (char *)malloc(ImgSize);
    getimage(2, 2, 21, 21, Remove);
    
    readimagefile("Lose.jpg", 0, 0, 426, 358);
    ImgSize= imagesize(0, 0, 426, 358);
    lose= (char *)malloc(ImgSize);
    getimage(0, 0, 426, 358, lose);
    
    readimagefile("gameover.jpg", 0, 0, pixel.Map_X+245, pixel.Map_Y);
    ImgSize= imagesize(0, 0, pixel.Map_X+245, pixel.Map_Y);
    gameOver= (char *)malloc(ImgSize);
    getimage(0, 0, pixel.Map_X+245, pixel.Map_Y, gameOver);
    
    // map information setup
	readimagefile("background.jpg", 0, 0, pixel.Map_X, pixel.Map_Y);// imagefile reading
    ImgSize= imagesize(0, 0, pixel.Map_X, pixel.Map_Y);// pixel(0,0)~(823,541) of size(1pixel is 4byte)
	Map= (char *)malloc(ImgSize);// memory allocation of map size
	getimage(0, 0, pixel.Map_X, pixel.Map_Y, Map);// image information mapping (0,0) ~ (448, 579) position
    
    readimagefile("nextblock.jpg", 0, 0, 147, 151);
    ImgSize= imagesize(0, 0, 147, 151);
    Next= (char *)malloc(ImgSize);
    getimage(0, 0, 147, 151, Next);
    
    readimagefile("score.jpg", 0, 0, 245, 77);
    ImgSize= imagesize(0, 0, 245, 77);
    Score= (char *)malloc(ImgSize);
    getimage(0, 0, 245, 77, Score);
    
    readimagefile("level.jpg", 0, 0, 245, 77);
    ImgSize= imagesize(0, 0, 245, 77);
    Level= (char *)malloc(ImgSize);
    getimage(0, 0, 245, 77, Level);
    
    readimagefile("help.jpg", 0, 0, 245, 300-pixel.Map_Y);
    ImgSize= imagesize(0, 0, 245, 300-pixel.Map_Y); 
    Help= (char *)malloc(ImgSize);
    getimage(0, 0, 245, 300-pixel.Map_Y, Help);
    
    
	BYTE block[KIND][BLOCKSIZE][BLOCKSIZE]=// 원본 블럭 
	{
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 4, 0, 0},
			{0, 4, 4, 4},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 5},
			{0, 5, 5, 5},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 7, 7, 0},
			{0, 7, 7, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 2, 2, 0},
			{2, 2, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 3, 0, 0},
			{3, 3, 3, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{6, 6, 0, 0},
			{0, 6, 6, 0},
			{0, 0, 0, 0}
		},			
	};

	BYTE remove[BLOCKSIZE][BLOCKSIZE];// 삭제할 블럭 
	BYTE CloneBlock[BLOCKSIZE][BLOCKSIZE];// 복사할 불럭 
	BYTE map[MAP_Y][MAP_X];
	
    Size MapSize, BlockSize;
	Pos BlockPos, RemovePos;
	BLock BlockInfo;
    
	char dir, CollisionState, DownToggle=1, stack, first=1;
	int move=0, delay=100;
	
	MapSize = SetSize(MapSize, MAP_Y, MAP_X);
	
	InitMap(MapSize, *map);
	
	InitBlock(&BlockInfo, &BlockSize, &BlockPos);
	
	
	
	CloneArr(BlockInfo, *block[BlockInfo.Kind], *CloneBlock);
    
    putimage(-2, -2, Map, 0);
    putimage(pixel.Map_X, 0, Next, 0);
    putimage(pixel.Map_X, 150, Score, 0);
    putimage(pixel.Map_X, 225, Level, 0);
    putimage(pixel.Map_X, 300, Help, 0);
    
    UpdateMap(MapSize, Block, pixel, *map);
    itoa(BlockInfo.Score, Pscore, 100);// convert to string
    itoa(BlockInfo.Level, Level, 10);
    
	outtextxy(pixel.Map_X+130, 190, Pscore);
	outtextxy(pixel.Map_X+130, 250, Level);
    PrtNextBlock(BlockInfo, Block, pixel, *block[BlockInfo.NextBlock]);
  
	while(1)
	{
            fflush(stdout);
            if(BlockInfo.Score>500)
            {
                SetLevel(&BlockInfo, BlockInfo.Level+1);
                SetScore(&BlockInfo, 0); 
                outtextxy(pixel.Map_X+130, 190, Pscore);
	            outtextxy(pixel.Map_X+130, 250, Level);
                SetDelay(&BlockInfo, BlockInfo.Delay-30);
            }
            
        if(IsBGMEnd())
        {
            m_dwDeviceID = m_mciOpenParms.wDeviceID;
			//seek to start
			mciSendCommandA(m_dwDeviceID, MCI_SEEK, MCI_SEEK_TO_START,(DWORD)(LPVOID)&m_mciPlayParms);
			//play repeat
			mciSendCommandA(m_dwDeviceID, MCI_PLAY, MCI_NOTIFY|MCI_DGV_PLAY_REPEAT,(DWORD)(LPVOID)&m_mciPlayParms);
        }
        
        PrtNextBlock(BlockInfo, Block, pixel, *block[BlockInfo.NextBlock]);
        CloneArr(BlockInfo, *CloneBlock, *remove);

		if(ChkGameOver(&BlockInfo, MapSize, *map) && !first)
		{
            putimage( (pixel.Map_X/2)-(426/2), (pixel.Map_Y/2)-(358/2), lose, 0);
            Sleep(1000);
            putimage(0, 0, gameOver, 0);
            Sleep(3000);
			break;
		}
		
		stack = ChkStack(MapSize, *map);		
		if(stack)
		{
            SetScore(&BlockInfo, BlockInfo.Score+100);
            printf("stack: %d\n", stack);
			RemoveStack(MapSize, stack, *map);
			stack=0;
			putimage(0, 0, Map, 0);
			
			itoa(BlockInfo.Score, Pscore, 10);// convert to string
		    outtextxy(pixel.Map_X+130, 190, Pscore);
			
            UpdateMap(MapSize, Block, pixel, *map);
            
            continue;
		}
		
		RemovePos = SetPos(RemovePos, BlockPos.X, BlockPos.Y);
		dir=ReadKey();

		CollisionState = ChkCollision(BlockInfo, MapSize, *map, *CloneBlock);
		//printf("blockpos: %d, %d\n", BlockPos.X, BlockPos.Y);
		//printf("CollisionState:%d\n", CollisionState);
		if(CollisionState==DOWNCOLLISION)
		{
			Stack(MapSize, BlockInfo, *map, *CloneBlock);
			UpdateMap(MapSize, Block, pixel, *map);
			
			BlockPos = SetPos(BlockPos, 3, 1);
			SetBlock(&BlockInfo, BlockPos, BlockSize);	
			SetRandom(&BlockInfo, KIND);
			
			CloneArr(BlockInfo, *block[BlockInfo.Kind], *CloneBlock);
			putimage(pixel.Map_X, 0, Next, 0);
			SetDelay(&BlockInfo, delay);
			continue;
		}
		
		else if(dir==RIGHT && CollisionState!= RIGHTCOLLISION)
		{
			BlockPos = SetPos(BlockPos, BlockPos.X+1, BlockPos.Y);
			move=1;
			sndPlaySoundA("SFX_SpecialLineClearSingle.wav",SND_NODEFAULT |SND_ASYNC);
		}
		
		else if(dir==LEFT && CollisionState!= LEFTCOLLISION)
		{
			BlockPos = SetPos(BlockPos, BlockPos.X-1, BlockPos.Y);
			move=1;
			sndPlaySoundA("SFX_SpecialLineClearDouble.wav",SND_NODEFAULT |SND_ASYNC);
		}
		
		else if(dir==DOWN && CollisionState!= DOWNCOLLISION)
		{
			BlockPos = SetPos(BlockPos, BlockPos.X, BlockPos.Y+1);
			move=1;
		    sndPlaySoundA("SFX_PieceLockdown.wav",SND_NODEFAULT |SND_ASYNC);
		}
		
		else if(dir==SPACE && CollisionState!= DOWNCOLLISION)
		{
			SetDelay(&BlockInfo, 1);
			BlockPos = SetPos(BlockPos, BlockPos.X, BlockPos.Y+1);
			move=1;
			sndPlaySoundA("drop.wav",SND_NODEFAULT |SND_ASYNC);
		}
		
		else if(dir==ROTATE && !CollisionState)
		{
			RotateArr(BlockInfo, *CloneBlock);
			move=1;
			sndPlaySoundA("SFX_PieceHardDrop.wav",SND_NODEFAULT |SND_ASYNC);
		}
		
		if(DownToggle%10==1)
		{
			DownToggle=1;
			BlockPos = SetPos(BlockPos, BlockPos.X, BlockPos.Y+1);
			move=1;
		}
		
		SetBlock(&BlockInfo, BlockPos, BlockSize);
		
        if(move || first)
		{
            Move(BlockInfo, RemovePos, Block, Remove, pixel, *CloneBlock, *remove);    
        }
		
		move=0;
        Sleep(BlockInfo.Delay);	
		CollisionState=FALSE;
		dir=FALSE;
		first=0;
        DownToggle++;
	}
	getch();
	return 0;
}

int IsBGMEnd(void)
{
	DWORD Length,Position;

	m_dwDeviceID = m_mciOpenParms.wDeviceID;

	m_mciStatusParms.dwItem = MCI_STATUS_LENGTH;
	if ( mciSendCommandA(m_dwDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&m_mciStatusParms) )
	return 0;

	//get wave file full length return value
	Length = m_mciStatusParms.dwReturn;

	m_mciStatusParms.dwItem = MCI_STATUS_POSITION ;
	if ( mciSendCommandA(m_dwDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&m_mciStatusParms) )
	return 0;

	//get wave file current play position return value
	Position = m_mciStatusParms.dwReturn;

	//current play position is equal full length?
	//equal : return 1
	//not equal : return 0
	if ( Length == Position )
	return 1;

	else
	return 0;
}
