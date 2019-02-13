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
    
    unsigned int size;
    
    char *UI_Name[7]=
         {
             "background.jpg",
             "background.jpg",
             "block.jpg",
             "block.jpg",
             "click_block.jpg",
             "clickop.jpg",
             "op.jpg",
         };
         
    char *UI[7];
    
    Size *UI_Size[7]=
        {
            &BackGroundSize,
            &ResultSize,
            &BlockSize,
            &ZeroBlockSize,
            &BlockSize,
            &BlockSize,
            &BlockSize,
        };
    
    
    Pos *ImgPos[8]=
    {
        &ClearPos,
        &PlusPos, 
        &SubPos, 
        &MultiPos, 
        &DividePos, 
        &OpenBracketPos, 
        &CloseBracketPos, 
        &EqualPos
    };
    
    Size *ImgSize[8]=
    {
        &BlockSize,
        &BlockSize,
        &BlockSize,
        &BlockSize,
        &BlockSize,
        &BlockSize,
        &BlockSize,
        &BlockSize
    };
    
    char *ImgText[8]=
    {
        "C",
        "+",
        "-",
        "*",
        "/",
        "(",
        ")",
        "="
    };
    
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
	
	for(i=0; i<7; i++)
    {
        readimagefile(*(UI_Name+i), 0, 0, (*(UI_Size+i))->Length, (*(UI_Size+i))->Height);
        size= imagesize(0, 0, (*(UI_Size+i))->Length, (*(UI_Size+i))->Height);
        *(UI+i)= (char *)malloc(size);
        getimage(0, 0, (*(UI_Size+i))->Length, (*(UI_Size+i))->Height, *(UI+i));
    }
    
    for(i=0; i<8; i++)
    {
        putimage( (*(ImgPos+i))->x, (*(ImgPos+i))->y, *(UI+6), 0);
        PrtTextToImg( *(*(ImgPos+i)), *(*(ImgSize+i)), TextOffsetPos, *(ImgText+i) );
    }
    
   
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            cnt+=1;
            itoa(cnt, Num, 10);
            
            BlockPos=SetPos(BlockPos, j*BlockSize.Length, (BlockSize.Height*3)+(i*BlockSize.Height));
            
            putimage(BlockPos.x, BlockPos.y, *(UI+2), 0);
            PrtTextToImg(BlockPos, BlockSize, TextOffsetPos, Num);
        }
    }
    
    putimage(0, BlockSize.Height*6, *(UI+3), 0);
    BlockPos=SetPos(BlockPos, 0, BlockSize.Height*6);
    PrtTextToImg(BlockPos, ZeroBlockSize, TextOffsetPos, "0");
    
    putimage(0, 0, *(UI+1), 0);
    
    
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
                
                if( ChkClickImg(MousePos, BlockPos, BlockSize) )
                {
                    num*=10;
                    num+=cnt;
                    
                    itoa(cnt, First, 10);
                    strcat(Val, First);
                    printf("%d", cnt);
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
            printf("%d", 0);
        }
        
        PrtTextToImg(ResultPos, ResultSize, ResultOffsetPos, Val);
        
        for(i=0; i<7; i++)
        {
            if( ChkClickImg(MousePos, *(*(ImgPos+i)), BlockSize) )
            {
                key= **(ImgText+i);
                
                if(num!=0)
                {
                    ListInsert(&list, num);
                }
                
                ListInsert(&list, key);
                num=0;
                
                printf("%s\n", *(ImgText+i) );
                strcat(Val, *(ImgText+i) );
            }
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
                //printf("\t\t <num: %d>\n", num);
                //printf("\n\n");
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
    
    getch();
    
	closegraph( );
	return 0;
}
