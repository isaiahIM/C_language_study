#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

#include "calc.h"
#include "CalcList.h"
#include "MyGraphic.h"

int main( )
{
    Pos MousePos, ResultPos, ClearPos;
	Pos PlusPos, SubPos, MultiPos, DividePos, OpenBracketPos, CloseBracketPos, EqualPos;
	
    Size NumSize, ResultSize, ClearSize;
	Size PlusSize, SubSize, MultiSize, DivideSize, EqualSize, BracketSize;
    
    unsigned int ImgSize;
    char *Number[10], *Plus, *Equal, *Result, *Clear, *SubStract, *Multiplex, *Division, *OpenBracket, *CloseBracket;
    
    char First[20]={'\0',}, Val[20]={'\0',};
    int i, first=1;
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
    
    initwindow( 640 , 480 , "clac" );
	
    NumSize= SetSize(NumSize, 44, 67);
    EqualSize= SetSize(EqualSize, 220,  67);
    ResultSize= SetSize(ResultSize, 220, 170);
    ClearSize= SetSize(ClearSize, 132, 67);
    PlusSize= SetSize(PlusSize, 132, 67);
    SubSize= SetSize(SubSize, 132, 67);
    MultiSize= SetSize(MultiSize, 132, 67);
    DivideSize= SetSize(DivideSize, 132, 67);
    BracketSize= SetSize(BracketSize, 132/2, 67);
        
	MousePos= SetPos(MousePos, 650, 480);
	PlusPos= SetPos(PlusPos, 220, 0); 
	EqualPos= SetPos(EqualPos, 0, 134);
	ResultPos= SetPos(ResultPos, 0, 201);
	ClearPos=SetPos(ClearPos, 220, 134);
	SubPos= SetPos(SubPos, 220, 67);
	MultiPos= SetPos(MultiPos, 220+132, 0);
	DividePos= SetPos(DividePos, 220+132, 67);
	OpenBracketPos= SetPos(OpenBracketPos, 220+132+132, 0);
    CloseBracketPos= SetPos(CloseBracketPos, 220+132+132+66, 0);
		
	
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
    
    readimagefile("multiplex.jpg", 0, 0, MultiSize.Length, MultiSize.Height);
    ImgSize= imagesize(0, 0, MultiSize.Length, MultiSize.Height);
    Multiplex= (char *)malloc(ImgSize);
    getimage(0, 0, MultiSize.Length, MultiSize.Height, Multiplex);
    
    readimagefile("division.jpg", 0, 0, DivideSize.Length, DivideSize.Height);
    ImgSize= imagesize(0, 0, DivideSize.Length, DivideSize.Height);
    Division= (char *)malloc(ImgSize);
    getimage(0, 0, DivideSize.Length, DivideSize.Height, Division);
    
    readimagefile("o_bracket.jpg", 0, 0, BracketSize.Length, BracketSize.Height);
    ImgSize= imagesize(0, 0,  BracketSize.Length, BracketSize.Height);
    OpenBracket= (char *)malloc(ImgSize);
    getimage(0, 0,  BracketSize.Length, BracketSize.Height, OpenBracket);
    
    readimagefile("c_bracket.jpg", 0, 0, BracketSize.Length, BracketSize.Height);
    ImgSize= imagesize(0, 0,  BracketSize.Length, BracketSize.Height);
    CloseBracket= (char *)malloc(ImgSize);
    getimage(0, 0,  BracketSize.Length, BracketSize.Height, CloseBracket);

    
    putimage(EqualPos.x, EqualPos.y, Equal, 0);
    putimage(PlusPos.x, PlusPos.y, Plus, 0);
    putimage(ResultPos.x, ResultPos.y, Result, 0);
    putimage(SubPos.x, SubPos.y, SubStract, 0);
    putimage(ClearPos.x, ClearPos.y, Clear, 0);
    putimage(MultiPos.x, MultiPos.y, Multiplex, 0);
    putimage(DividePos.x, DividePos.y, Division, 0);
    putimage(OpenBracketPos.x, OpenBracketPos.y, OpenBracket, 0);
    putimage(CloseBracketPos.x, CloseBracketPos.y, CloseBracket, 0);
    
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
        MousePos = GetClick();
        
        for(i=0; i<5; i++)
        {
            if( (MousePos.x > i*NumSize.Length && MousePos.x < (i+1)*NumSize.Length)
                &&(MousePos.y > 0 && MousePos.y < NumSize.Height) )
            {
                num*=10;
                num+=i;
                
                itoa(i, First, 10);
                strcat(Val, First);
                printf("%d\n", i);
                first=0;
            }
             
            else if(( MousePos.x > i*NumSize.Length && MousePos.x < (i+1)*NumSize.Length)
                     &&(MousePos.y > NumSize.Height && MousePos.y < 2*(NumSize.Height)) )
            {
                num*=10;
                num+=i+5;
                
                itoa(i+5, First, 10);
                strcat(Val, First);
                printf("%d\n", i+5);
                first=0;
            }
        }
        
        outtextxy(ResultPos.x+(ResultSize.Length/2)-40, ResultPos.y+(ResultSize.Height/2), Val);
        
        
        if( ChkClickImg(MousePos, PlusPos, PlusSize) )
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
        
        else if( ChkClickImg(MousePos, SubPos, SubSize) )
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
        
        else if( ChkClickImg(MousePos, MultiPos, MultiSize) )
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
        
        else if( ChkClickImg(MousePos, DividePos, DivideSize) )
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
        
        else if( ChkClickImg(MousePos, OpenBracketPos, BracketSize) )
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
        
        else if( ChkClickImg(MousePos, CloseBracketPos, BracketSize) )
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

        if( ChkClickImg(MousePos, EqualPos, EqualSize) )
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
            printf("\nResult: %.4lf\n", result);
            
            strcat(Val, " = ");
            strcat(Val, itoa((int)GetResult(&PostFix), First, 10) );
        }// end of if( ChkClickImg(MousePos, EqualPos, EqualSize) )
        
        if(ChkClickImg(MousePos, ClearPos, ClearSize) )
        {
            num=0;
            printf("clear!\n\n");
            system("cls");
            
            ClearList(&stack);
            ClearList(&PostFix);
            ClearList(&list);
            
            ClearArr(Val);
            ClearArr(First);
            outtextxy(ResultPos.x+(ResultSize.Length/2)-40, ResultPos.y+(ResultSize.Height/2), "                    ");
        }
        
        MousePos= SetPos(MousePos, 640, 480);
        
    }// end of while(1)
    
	closegraph( );
	return( 0 );
}
