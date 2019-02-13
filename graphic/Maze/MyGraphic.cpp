#include "MyGraphic.h"


ImgSize SetImgSize(int Length, int Height)
{
    ImgSize Img;
    
    Img.Length=Length;
    Img.Height=Height;
    
    return Img;
}

ImgPos SetImgPos(int x, int y)
{
    ImgPos pos;
    
    pos.x=x;
    pos.y=y;
    
    return pos;
}

ImgPos ConvImgPos(Pos *pos, int GapSize)
{
    ImgPos imgPos;
    imgPos.x= (pos->x)*GapSize;
    imgPos.y= (pos->y)*GapSize;
    
    return imgPos;
}

void SetImgInfo(char *ImgName, ImgSize size, char **Img)
{
    unsigned int imgSize;
    
    readimagefile(ImgName, 0, 0, size.Length, size.Height);
    imgSize= imagesize(0, 0, size.Length, size.Height);
    *Img= (char *)malloc(imgSize);
    getimage(0, 0, size.Length, size.Height, *Img);
}

void DisplayImg(ImgPos pos, char *Img)
{
    putimage(pos.x, pos.y, Img, 0);
}


void DisplayMaze_Graphic(Size MazeSize, Maze *maze, int GapSize, char *Img_Wall, char *Img_Empty)
{
    int i, j;
    ImgPos pos;
    
    for(i=0; i<MazeSize.Height; i++)
    {
        for(j=0; j<MazeSize.Length; j++)
        {
            if( *(maze+(MazeSize.Length*i)+j) )
            {
                pos= SetImgPos(j*GapSize, i*GapSize);
                DisplayImg(pos, Img_Wall);
            }
            else
            {
                pos= SetImgPos(j*GapSize, i*GapSize);
                DisplayImg(pos, Img_Empty); 
            }
        }
    }
}

void DisplayTrace_Graphic(Pos TracePos, Pos *HistoryPos, char *Img_Tracer, char *Img_BackGround, int GapSize)
{
    DisplayImg(SetImgPos( (TracePos.x*GapSize), TracePos.y*GapSize), Img_Tracer);
    
    if(HistoryPos!=NULL)
    {
        DisplayImg(SetImgPos( (HistoryPos->x*GapSize), HistoryPos->y*GapSize), Img_BackGround);
    }
}


