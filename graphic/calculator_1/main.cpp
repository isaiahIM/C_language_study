#include <stdio.h>
#include <string.h>
#include <graphics.h>


enum CalcType
{
PLUS=1,
SUBSTRACT,
MULTIPLEX,
DIVISION
};
typedef struct _POS
{
    int x;
    int y;
} Pos;

typedef struct _SIZE
{
    int Length;
    int Height;
} Size;

int ChkClickImg(Pos ClickPos, Pos ImgPos, Size ImgSize);// clck image checking function

Pos SetPos(Pos pos, int x, int y);
Size SetSize(Size size, int Length, int Height);

int main( )
{
    Pos MousePos, PlusPos, EqualPos, ResultPos, ClearPos, SubPos, MultiPos, DividePos;
	Size NumSize, PlusSize, EqualSize, ResultSize, ClearSize, SubSize, MultiSize, DivideSize;
	
    unsigned int ImgSize;
    char *Number[10], *Plus, *Equal, *Result, *Clear, *SubStract, *Multiplex, *Division;
    
    char First[20]={0,}, Second[20]={0,}, Val[20]={0,};
    int i, first=0, second=0, buffer=0, change=0, CalcType, val;

    initwindow( 640 , 480 , "clac" );
	
    NumSize=SetSize(NumSize, 44, 67);
    EqualSize=SetSize(EqualSize, 220,  67);
    ResultSize=SetSize(ResultSize, 220, 170);
    ClearSize= SetSize(ClearSize, 132, 67);
    PlusSize=SetSize(PlusSize, 132, 67);
    SubSize= SetSize(SubSize, 132, 67);
    MultiSize= SetSize(MultiSize, 132, 67);
    DivideSize= SetSize(DivideSize, 132, 67);
        
	MousePos= SetPos(MousePos, 650, 480);
	PlusPos= SetPos(PlusPos, 220, 0); 
	EqualPos= SetPos(EqualPos, 0, 134);
	ResultPos= SetPos(ResultPos, 0, 201);
	ClearPos=SetPos(ClearPos, 220, 134);
	SubPos= SetPos(SubPos, 220, 67);
	MultiPos= SetPos(MultiPos, 220+132, 0);
	DividePos= SetPos(DividePos, 220+132, 67);
	
	readimagefile("0.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[0]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[0]);
	
	readimagefile("1.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[1]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[1]);
	
	readimagefile("2.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[2]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[2]);
    
    readimagefile("3.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[3]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[3]);
    
    readimagefile("4.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[4]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[4]);
    
    readimagefile("5.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[5]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[5]);
    
    readimagefile("6.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[6]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[6]);
    
    readimagefile("7.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[7]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[7]);
    
    readimagefile("8.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[8]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[8]);
    
   	readimagefile("9.jpg", 0, 0, NumSize.Length, NumSize.Height);
    ImgSize= imagesize(0, 0, NumSize.Length, NumSize.Height);
    Number[9]= (char *)malloc(ImgSize);
    getimage(0, 0, NumSize.Length, NumSize.Height, Number[9]);
    
    readimagefile("equal.jpg", 0, 0, EqualSize.Length, EqualSize.Height);
    ImgSize= imagesize(0, 0,  EqualSize.Length, EqualSize.Height);
    Equal= (char *)malloc(ImgSize);
    getimage(0, 0,  EqualSize.Length, EqualSize.Height, Equal);
    
    readimagefile("result.jpg", 0, 0, ResultSize.Length, ResultSize.Height);
    ImgSize= imagesize(0, 0, ResultSize.Length, ResultSize.Height);
    Result= (char *)malloc(ImgSize);
    getimage(0, 0, ResultSize.Length, ResultSize.Height, Result);
    
    readimagefile("clear.jpg", 0, 0, ClearSize.Length, ClearSize.Height);
    ImgSize= imagesize(0, 0, ClearSize.Length, ClearSize.Height);
    Clear= (char *)malloc(ImgSize);
    getimage(0, 0, ClearSize.Length, ClearSize.Height, Clear);
    
    readimagefile("plus.jpg", 0, 0, PlusSize.Length, PlusSize.Height);
    ImgSize= imagesize(0, 0, PlusSize.Length, PlusSize.Height);
    Plus= (char *)malloc(ImgSize);
    getimage(0, 0, PlusSize.Length, PlusSize.Height, Plus);
    
    readimagefile("substract.jpg", 0, 0, SubSize.Length, SubSize.Height);
    ImgSize= imagesize(0, 0, SubSize.Length, SubSize.Height);
    SubStract= (char *)malloc(ImgSize);
    getimage(0, 0, SubSize.Length, SubSize.Height, SubStract);
    
    readimagefile("multiplex.jpg", 0, 0, MultiSize.Length, MultiSize.Height);
    ImgSize= imagesize(0, 0, MultiSize.Length, MultiSize.Height);
    Multiplex= (char *)malloc(ImgSize);
    getimage(0, 0, MultiSize.Length, MultiSize.Height, Multiplex);
    
    readimagefile("division.jpg", 0, 0, DivideSize.Length, DivideSize.Height);
    ImgSize= imagesize(0, 0, DivideSize.Length, DivideSize.Height);
    Division= (char *)malloc(ImgSize);
    getimage(0, 0, DivideSize.Length, DivideSize.Height, Division);

    
    putimage(EqualPos.x, EqualPos.y, Equal, 0);
    putimage(PlusPos.x, PlusPos.y, Plus, 0);
    putimage(ResultPos.x, ResultPos.y, Result, 0);
    putimage(SubPos.x, SubPos.y, SubStract, 0);
    putimage(ClearPos.x, ClearPos.y, Clear, 0);
    putimage(MultiPos.x, MultiPos.y, Multiplex, 0);
    putimage(DividePos.x, DividePos.y, Division, 0);
    
    for(i=0; i<10; i++)
    {
        if(i>4)
        {
            putimage((i-5)*NumSize.Length, NumSize.Height, Number[i], 0);
        }
        else
        {
            putimage(i*NumSize.Length, 0, Number[i], 0);
        }
    }
    
    
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, MousePos.x, MousePos.y);
        }
        
        for(i=0; i<5; i++)
        {
            if( (MousePos.x > i*NumSize.Length && MousePos.x < (i+1)*NumSize.Length)
                &&(MousePos.y > 0 && MousePos.y < NumSize.Height) )
            {
                printf("%d", i);
                if(!change)
                {
                    buffer=i;
                    first*=10;
                    first+=buffer;
                    itoa(first, First, 10);// convert int to char*
                }
                else
                {
                    buffer=i;
                    second*=10;
                    second+=buffer; 
                    itoa(buffer, Second, 10);// convert int to char*
                    strcat(First, Second);
                }
            }
            
            else if(( MousePos.x > i*NumSize.Length && MousePos.x < (i+1)*NumSize.Length)
                     &&(MousePos.y > NumSize.Height && MousePos.y < 2*(NumSize.Height)) )
            {
                printf("%d", i+5);
                if(!change)
                {
                    buffer=i+5;
                    first*=10;
                    first+=buffer;
                    itoa(first, First, 10);// convert int to char*
                }
                else
                {
                    buffer=i+5;
                    second*=10;
                    second+=buffer; 
                    itoa(buffer, Second, 10);// convert int to char*
                    strcat(First, Second);// string connect
                }               
            }
        }
        
        outtextxy(ResultPos.x+(ResultSize.Length/2)-40, ResultPos.y+(ResultSize.Height/2), First);
        
        if( ChkClickImg(MousePos, PlusPos, PlusSize) )
        {
            printf(" + ");
            change=1;
            strcat(First, "+");
            CalcType=PLUS;
        }
        
        else if( ChkClickImg(MousePos, SubPos, SubSize) )
        {
            printf(" - ");
            change=1;
            strcat(First, " - ");
            CalcType=SUBSTRACT;
        }
        
        else if( ChkClickImg(MousePos, MultiPos, MultiSize) )
        {
            printf(" * ");
            change=1;
            strcat(First, " * ");
            CalcType=MULTIPLEX;
        }
        
        else if( ChkClickImg(MousePos, DividePos, DivideSize) )
        {
            printf(" / ");
            change=1;
            strcat(First, " / ");
            CalcType=DIVISION;
        }
       
        
        if( ChkClickImg(MousePos, EqualPos, EqualSize) )
        {
            if(CalcType==PLUS)
            {
                val=first+second;
            }
            
            else if(CalcType==SUBSTRACT)
            {
                val=first-second;
            }
            
            else if(CalcType==MULTIPLEX)
            {
                val=first*second;
            }
            
            else if(CalcType==DIVISION)
            {
                val=first/second;
            }
            
            printf("= %d\n", val);
            strcat(First, "= ");
            itoa(val, Val, 10);
            strcat(First, Val);
            
            change=0;
            first=0, second=0;
        }
        
        if(ChkClickImg(MousePos, ClearPos, ClearSize))
        {
                                 
            for(i=0; i<19; i++)
            {
                First[i]=' ';
                //Sleep(100);
                printf(" %d Clear", i);
                //outtextxy(ResultPos.x+(ResultSize.Length/2)-40, ResultPos.y+(ResultSize.Height/2), First);
            }
        }
        
        MousePos= SetPos(MousePos, 640, 480);
    }
    
	closegraph( );
	return( 0 );
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
