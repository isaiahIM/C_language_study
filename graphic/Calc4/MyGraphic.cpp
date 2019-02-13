#include"MyGraphic.h"

void ClearArr(char *arr)
{
    arr[0]='\0';
}

void PrtTextToImg(Pos ImgPos, Size ImgSize, Pos OffsetPos, char *text)
{
    Pos TextPos;
    
    TextPos= CenterImg(ImgPos, ImgSize, OffsetPos);
    outtextxy(TextPos.x, TextPos.y, text);
}

Pos GetClick(void)
{
    Pos MousePos;
    if(IsClickDown())
    {
        getmouseclick(WM_LBUTTONDOWN, MousePos.x, MousePos.y);
    }
    else
    {
        MousePos= SetPos(MousePos, 0 ,0);
    }
    return MousePos;
}

Pos SetPos(Pos pos, int x, int y)
{
    pos.x=x;
    pos.y=y;
    return pos;
}

Pos CenterImg(Pos ImgPos, Size ImgSize, Pos offset)
{
    Pos Center;
    
    Center=SetPos(Center, ImgPos.x+(ImgSize.Length/2)+offset.x, ImgPos.y+(ImgSize.Height/2)+offset.y);
    return Center;
}

Size SetSize(Size size, int Length, int Height)
{
    size.Length=Length;
    size.Height=Height;
    return size;
}

int ChkClickImg(Pos ClickPos, Pos ImgPos, Size ImgSize)
{
   if( (ClickPos.x > ImgPos.x && ClickPos.x < ImgPos.x + ImgSize.Length)
     &&(ClickPos.y > ImgPos.y && ClickPos.y < ImgPos.y + ImgSize.Height) )
   {
       return TRUE;                      
   }
   else
   return FALSE;
}

int IsClickDown(void)
{
    if( ismouseclick(WM_LBUTTONDOWN ) )
    {
        return TRUE;
    }
    return FALSE;
}

