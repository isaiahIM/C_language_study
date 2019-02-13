#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

#include "calc.h"
#include "CalcList.h"
#include "MyGraphic.h"

int main( )
{
    Pos MousePos, ResultPos, ClearPos, BlockPos;
	Pos PlusPos, SubPos, MultiPos, DividePos, OpenBracketPos, CloseBracketPos, EqualPos;
	Pos TextPos, TextOffsetPos, ResultOffsetPos;
	
	Size BlockSize, ZeroBlockSize, BackGroundSize, ResultSize;
    
    unsigned int ImgSize;
    char *Block, *ClickBlock, *Op, *ClickOp, *BackGround, *ZeroBlock, *Result;
    
    
    char Num[1];
    
    char First[20]={'\0',}, Val[20]={'\0',};
    int i, j, first=1, cnt=0;
    Data num=0;
    double result=0;
    
    List list, PostFix, stack;
    Data key;
    
    InitList(&list);
    InitList(&PostFix);
    InitList(&stack);
    
    LFirst(&list);
    LFirst(&PostFix);
    LFirst(&stack);
    
    initwindow(280, 420, "clac");
    
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	
	BackGroundSize= SetSize(BackGroundSize, 280, 420);
    BlockSize= SetSize(BlockSize, BackGroundSize.Length/4, BackGroundSize.Height/7);
    ZeroBlockSize= SetSize(ZeroBlockSize, BlockSize.Length*3, BlockSize.Height);
    ResultSize= SetSize(ResultSize, BackGroundSize.Length, BlockSize.Height*2);
    
    
	MousePos= SetPos(MousePos, 0, 0);
	EqualPos= SetPos(EqualPos, BlockSize.Length*3, ResultSize.Height);
	ResultPos= SetPos(ResultPos, 0, 0);
	ClearPos=SetPos(ClearPos, 0, ResultSize.Height);
	
    PlusPos= SetPos(PlusPos, BlockSize.Length*3, BlockSize.Height*3); 
	SubPos= SetPos(SubPos, BlockSize.Length*3, BlockSize.Height*4);
	MultiPos= SetPos(MultiPos, BlockSize.Length*3, BlockSize.Height*5);
	DividePos= SetPos(DividePos, BlockSize.Length*3, BlockSize.Height*6);
	
    OpenBracketPos= SetPos(OpenBracketPos, BlockSize.Length, ResultSize.Height);
    CloseBracketPos= SetPos(CloseBracketPos, BlockSize.Length*2, ResultSize.Height);
	TextOffsetPos=SetPos(TextOffsetPos, -10, -10);
	ResultOffsetPos=SetPos(ResultOffsetPos, TextOffsetPos.x-100, TextOffsetPos.y);
	
	readimagefile("background.jpg", 0, 0, BackGroundSize.Length, BackGroundSize.Height);
    ImgSize= imagesize(0, 0, BackGroundSize.Length, BackGroundSize.Height);
    BackGround= (char *)malloc(ImgSize);
    getimage(0, 0, BackGroundSize.Length, BackGroundSize.Height, BackGround);
    
    readimagefile("background.jpg", 0, 0, ResultSize.Length, ResultSize.Height);
    ImgSize= imagesize(0, 0, ResultSize.Length, ResultSize.Height);
    Result= (char *)malloc(ImgSize);
    getimage(0, 0, ResultSize.Length, ResultSize.Height, Result);
	
	readimagefile("block.jpg", 0, 0, BlockSize.Length, BlockSize.Height);
    ImgSize= imagesize(0, 0, BlockSize.Length, BlockSize.Height);
    Block= (char *)malloc(ImgSize);
    getimage(0, 0, BlockSize.Length, BlockSize.Height, Block);
    
    readimagefile("block.jpg", 0, 0, ZeroBlockSize.Length, ZeroBlockSize.Height);
    ImgSize= imagesize(0, 0, ZeroBlockSize.Length, ZeroBlockSize.Height);
    ZeroBlock= (char *)malloc(ImgSize);
    getimage(0, 0, ZeroBlockSize.Length, ZeroBlockSize.Height, ZeroBlock);
	
	readimagefile("click_block.jpg", 0, 0, BlockSize.Length, BlockSize.Height);
    ImgSize= imagesize(0, 0, BlockSize.Length, BlockSize.Height);
    ClickBlock= (char *)malloc(ImgSize);
    getimage(0, 0, BlockSize.Length, BlockSize.Height, ClickBlock);
    
    readimagefile("clickop.jpg", 0, 0, BlockSize.Length, BlockSize.Height);
    ImgSize= imagesize(0, 0, BlockSize.Length, BlockSize.Height);
    ClickOp= (char *)malloc(ImgSize);
    getimage(0, 0, BlockSize.Length, BlockSize.Height, ClickOp);

    readimagefile("op.jpg", 0, 0, BlockSize.Length, BlockSize.Height);
    ImgSize= imagesize(0, 0, BlockSize.Length, BlockSize.Height);
    Op= (char *)malloc(ImgSize);
    getimage(0, 0, BlockSize.Length, BlockSize.Height, Op);
    
    
    putimage(EqualPos.x, EqualPos.y, Op, 0);
    PrtTextToImg(EqualPos, BlockSize, TextOffsetPos, "=");
    
    putimage(PlusPos.x, PlusPos.y, Op, 0);
    PrtTextToImg(PlusPos, BlockSize, TextOffsetPos, "+");
    
    putimage(SubPos.x, SubPos.y, Op, 0);
    PrtTextToImg(SubPos, BlockSize, TextOffsetPos, "-");
    
    putimage(ClearPos.x, ClearPos.y, Op, 0);
    PrtTextToImg(ClearPos, BlockSize, TextOffsetPos, "C");
    
    putimage(MultiPos.x, MultiPos.y, Op, 0);
    PrtTextToImg(MultiPos, BlockSize, TextOffsetPos, "*");
    
    putimage(DividePos.x, DividePos.y, Op, 0);
    PrtTextToImg(DividePos, BlockSize, TextOffsetPos, "/");
    
    putimage(OpenBracketPos.x, OpenBracketPos.y, Op, 0);
    PrtTextToImg(OpenBracketPos, BlockSize, TextOffsetPos, "(");
    
    putimage(CloseBracketPos.x, CloseBracketPos.y, Op, 0);
    PrtTextToImg(CloseBracketPos, BlockSize, TextOffsetPos, ")");
    
    putimage(ResultPos.x, ResultPos.y, Result, 0);
    
    
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            cnt+=1;
            
            itoa(cnt, Num, 10);
            BlockPos=SetPos(BlockPos, j*BlockSize.Length, (BlockSize.Height*3)+(i*BlockSize.Height));
            
            putimage(BlockPos.x, BlockPos.y, Block, 0);
            
            PrtTextToImg(BlockPos, BlockSize, TextOffsetPos, Num);
        }
    }
    
    putimage(0, BlockSize.Height*6, ZeroBlock, 0);
    
    BlockPos=SetPos(BlockPos, 0, BlockSize.Height*6);
    PrtTextToImg(BlockPos, ZeroBlockSize, TextOffsetPos, "0");
    
    
    while(1)
    {
        MousePos = GetClick();
        cnt=0;
        
        for(i=0; i<3; i++)
        {
            for(j=0; j<3; j++)
            {
                cnt+=1;
                BlockPos=SetPos(BlockPos, j*BlockSize.Length, (BlockSize.Height*3)+(i*BlockSize.Height));
                
                if( (MousePos.x > BlockPos.x && MousePos.x < BlockPos.x+BlockSize.Length)
                  &&(MousePos.y > BlockPos.y && MousePos.y < BlockPos.y+BlockSize.Height) )
                {
                    num*=10;
                    num+=cnt;
                    
                    itoa(cnt, First, 10);
                    strcat(Val, First);
                    printf("%d\n", cnt);
                    first=0;
                }
            }
        }
        
        BlockPos=SetPos(BlockPos, 0, BlockSize.Height*6);
        if( ChkClickImg(MousePos, BlockPos, ZeroBlockSize) )
        {
            num*=10;
            num+=0;
            
            itoa(0, First, 10);
            strcat(Val, First);
            printf("%d\n", 0);
        }
        
        //settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        PrtTextToImg(ResultPos, ResultSize, ResultOffsetPos, Val);
        //settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        
        if( ChkClickImg(MousePos, PlusPos, BlockSize) )
        {
            key='+';
            if(num!=0)
            {
                ListInsert(&list, num);
            }
            
            ListInsert(&list, key);
            num=0;
            
            printf("+\n");
            strcat(Val, " + ");
        }
        
        else if( ChkClickImg(MousePos, SubPos, BlockSize) )
        {
            key='-';
            if(num!=0)
            {
                ListInsert(&list, num);
            }
            
            else if(first)
            {
                printf("First state\n");
                ListInsert(&list, num);
                first=0;
            }
            
            ListInsert(&list, key);
            num=0;
            
            strcat(Val, " - ");
        }
        
        else if( ChkClickImg(MousePos, MultiPos, BlockSize) )
        {
            key='*';
            if(num!=0)
            {
                ListInsert(&list, num);
            }
            ListInsert(&list, key);
            num=0;
            
            strcat(Val, " * ");
        }
        
        else if( ChkClickImg(MousePos, DividePos, BlockSize) )
        {
            key='/';
            if(num!=0)
            {
                ListInsert(&list, num);
            }
            ListInsert(&list, key);
            num=0;
            
            strcat(Val, " / ");
        }
        
        else if( ChkClickImg(MousePos, OpenBracketPos, BlockSize) )
        {
            key='(';
            if(num!=0)
            {
                ListInsert(&list, num);
            }
            //printf("\t\tnum:%d\n", num);
            ListInsert(&list, key);
            num=0;
            
            strcat(Val, " ( ");
        }
        
        else if( ChkClickImg(MousePos, CloseBracketPos, BlockSize) )
        {
            key=')';
            if(num!=0)
            {
                ListInsert(&list, num);
            }
            ListInsert(&list, key);
            num=0;
            
            strcat(Val, " ) ");
        }

        if( ChkClickImg(MousePos, EqualPos, BlockSize) )
        {
            key='=';
            printf("\n\n\n");
            if(key== '=')
            {
                if(num!=0)
                {
                    ListInsert(&list, num);
                }
            }
            
            PrtList(&list);
    
            ConvertToPostFix(&list, &PostFix, &stack);
            printf("\n\n<PostFix>\n");
            PrtList(&PostFix);
            
            CalculatePostFix(&PostFix);
            result= GetResult(&PostFix);
            printf("\nResult: %lf\n", result);
            
            strcat(Val, " = ");
            strcat(Val, itoa((int)GetResult(&PostFix), First, 10) );
        }// end of if( ChkClickImg(MousePos, EqualPos, EqualSize) )
        
        if(ChkClickImg(MousePos, ClearPos, BlockSize) )
        {
            num=0;
            printf("clear!\n\n");
            system("cls");
            
            ClearList(&stack);
            ClearList(&PostFix);
            ClearList(&list);
            
            ClearArr(Val);
            ClearArr(First);
            PrtTextToImg(ResultPos, ResultSize, ResultOffsetPos, "                                          ");
        }
        
        MousePos= SetPos(MousePos, 0, 0);
    }// end of while(1)
    
	closegraph( );
	return 0;
}
