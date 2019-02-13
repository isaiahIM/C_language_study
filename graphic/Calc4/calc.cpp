#include<Windows.h>
#include<conio.h>
#include "calc.h"
#define DEBUG 0
/*
calc.h Reference:
       
typedef struct DEQUE_LIST
{
    Data Arr[ArrSize];
    int Count;
    int now;
    
    double Result;
} List;

void InitList(List *list);

void ListInsert(List *list, Data data);

void PrtList(List *list);
Data RemoveList(List *list);

void SetToken(List *list, Data Token);

Data PopStack(List *list);
Data PeekStack(List *list);

Data PopQueue(List *list);
Data PeekQueue(List *list);

Data GetNow(List *list);

int IsEmptyList(List *list);

int LFirst(List *list);
int LNext(List *list);
int LPrev(List *list);
int Llast(List *list);

*/


void CalculatePostFix(List *list)
{
    printf("\n\n<CalculatePostFix function>");
    LFirst(list);
    
    List ListStack;// stack list
    Data Arit;
    double d1, d2;
    
    LFirst(list);
    
    InitList(&ListStack);
    
    while(!IsOp(list))
    {
        LNext(list);
    }
    
    Arit=RemoveList(list);
    //printf("now: %d\n", GetNow(list));
    d1=RemoveList(list);
    d2=RemoveList(list);
    
    if(DEBUG)
    {
        printf("now: %d\n", GetNow(list));
        printf("Arit: %c\n", Arit);
        printf("d1: %d\n", d1);
        printf("d2: %d\n", d2);
    }
    
    switch(Arit)// first value calculate
    {
        case '+':
             WriteResult(list, d1+d2);
             break;
        
        case '-':
             WriteResult(list, d1-d2);
             break;
             
        case '*':
             WriteResult(list, d1*d2);
             break;
             
        case '/':
             WriteResult(list, d1/d2);
             break;
             
        default:
            printf("\n\n\t\t\terror!! error is %c\n", Arit);
            break;
    }
    
    while(!IsEmptyList(list))
    {
        while(!IsOp(list))
        {
            LNext(list);
        }
        
        Arit=RemoveList(list);
        
        d1=RemoveList(list);
        d2=GetResult(list);
        
        printf("d1: %d\n", d1);
        printf("d2: %d\n", d2);
        switch(Arit)// first value calculate
        {
            case '+':
                 WriteResult(list, d1+d2);
                 break;
            
            case '-':
                 WriteResult(list, d1-d2);
                 break;
                 
            case '*':
                 WriteResult(list, d1*d2);
                 break;
                 
            case '/':
                 WriteResult(list, d1/d2);
                 break;
                 
            default:
                printf("\n\t\t\terror!! error is %c\n", Arit);
                break;
        }
    }// end of while(LNext(list))"
}

void ConvertToPostFix(List *Original, List *Convert, List *stack)
{
    printf("\n<ConvertToPostFix>\n");
    
    Data Before, After;// Arithmetic value
    
    LFirst(Original);
    LFirst(Convert);
    LFirst(stack);
    
    if(IsOp(Original))
    {
        if(DEBUG)
        {
            printf("<Original is op>\n");
        }
        
        Before=GetNow(Original);
        ListInsert(stack, Before);
        LNext(Original);
        
        if(DEBUG)
        {
            printf("\t<Op Insert finish!!>\n");
        }
    }
    
    if(!IsOp(Original))
    {
         ListInsert(Convert, GetNow(Original));
         LNext(Original);
    }
    
    if(IsOp(Original))
    {
        ListInsert(stack, GetNow(Original));
        //LNext(Original);
    }
    
    if(DEBUG)
    {
        printf("peek: %c\n", PeekStack(stack));
	    printf("\n\n");
    }
    
    /*next loop*/
    while(LNext(Original))// MainLoop
    {
        if(DEBUG)
        printf("\nGetNow(Otiginal): %d\n", GetNow(Original));
        
        if(IsOp(Original))
        {
            if(DEBUG)
            printf("\nop!\n");
            
            After=ConvertToOp(GetNow(Original));
            
            if(DEBUG)
            printf("aftet: %d\n", After);
            
            if(GetNow(Original)=='(')
            {
                ListInsert(stack, GetNow(Original));
            }
            
            else if(GetNow(Original)== ')' )
            {
                while('(' != PeekStack(stack) && !IsEmptyList(stack))
                {
                    if(DEBUG)
                    printf("\tpop! is :%c\n", PeekStack(stack));
                    
                    ListInsert(Convert, PopStack(stack));
                    //Sleep(2000);
                }
                if(DEBUG)
                {
                    printf("\n\n");
                    printf("A Peek: %c, now is %d\n", PeekStack(stack), stack->now);
                    printf("%c is pop finish!\n", PopStack(stack) );
                    printf("\n\t\t\tpeek: %c\n", PeekStack(stack) );
                }
                if(!DEBUG)
                {
                    PopStack(stack);
                }
                
            }// end bracket
            else
            {
                Before=ConvertToOp(PeekStack(stack));
                if(DEBUG)
                {
                    printf("\t\tbefore:%d after:%d\n", Before, After);
				    printf("IsBigOp: %d\n", IsBigOp(Before, After));
                }
                
                while(!IsBigOp(Before, After)&& (!IsEmptyList(stack)) )
                {
                    Before=ConvertToOp(PeekStack(stack));
                    
                    if(DEBUG)
                    {
                        printf("%c type is Pop!\n", PeekStack(stack));
                        printf("\tConvert\n");
                    }
                    
                    ListInsert(Convert, PopStack(stack));
                }
                
                ListInsert(stack, GetNow(Original));   
            }// end of else
            
        }// end of if(IsOp(Original))

        else
        {
            if(DEBUG)
            {
                printf("\nnum!\n");
                printf("now is %d\n", Original->now);
            }
            
            ListInsert(Convert, GetNow(Original));
        }
        
    }// end of while(LNext(Original))
    
    while(!IsEmptyList(stack))// last calculate.(all of pop stack)
    {
        if(DEBUG)
        {
            printf("\nloop Finish\n");
            printf("Stack: %d, %d\n", stack->now, stack->Count);
            printf("stack type is %c\n", PeekStack(stack));
        }
        
        ListInsert(Convert, PopStack(stack));
    }
    printf("Finish!\n\n\n\n\n");
}

void ClearList(List *list)
{
    InitList(list);
}


char GetKey(void)
{
    char val;
    val= getch();
    
    return val;
}

int ConvertToInt(char num)
{
    return num-48;
}

int ConvertToOp(char key)
{
    switch(key)
    {
        case '*':
        case '/':
             return 3;
             
        case '+':
        case '-':
             return 2;
             
        case '(':
        case ')':
             return 1;
             
        default:
             return -1;
    }
}
/*
#define PLUS 2
#define SUBSTRACT 2

#define MULTIPLEX 3
#define DIVISION 3
*/
int IsBigOp(Data Before, Data New)
{
    if(Before<=New)
    {
        return 1;
    }
    
    else if(Before>New)
    {
        return 0;
    }
    else
    {
        return 2;
    }
}

int CkhCalcOp(char key)
{
    switch(key)
    {
        case '+' :
        case '-' :
        case '*' :
        case '/' :
        case '(' :
        case ')' :
             return 1;
             
        default:
            return 0;
    }
}

int IsNum(List *list)
{
    if( (*(list->Arr+(list->now))) >='0' && (*(list->Arr+(list->now))) <= '9')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int IsOp(List *list)
{
    switch(list->Arr[list->now])
    {
        case '+' :
        case '-' :
        case '*' :
        case '/' :
        case '(' :
        case ')' :
             return TRUE;
             
        default:
            return FALSE;
    }
}


