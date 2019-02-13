#include"MyGraphic.h"

void ClearArr(char *arr)
{
    arr[0]='\0';
}


Pos GetClick(void)
{
    Pos MousePos;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, MousePos.x, MousePos.y);
    }
    return MousePos;
}

Pos SetPos(Pos pos, int x, int y)
{
    pos.x=x;
    pos.y=y;
    return pos;
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
