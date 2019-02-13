#include<Windows.h>
#include "calc.h"

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
    Data d1, d2, Arit;
    LFirst(list);
    
    InitList(&ListStack);
    
    while(!IsOp(list))
    {
        LNext(list);
    }
    
    Arit=RemoveList(list);
    
    d2=RemoveList(list);
    d1=RemoveList(list);
    
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
            printf("\t\t\terror!! error is %d\n", Arit);
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
                printf("\t\t\terror!! error is %d\n", Arit);
                break;
        }
        
    }// end of while(LNext(list))
    
   // list->Result=GetNow(&ListStack);
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
        Before=GetNow(Original);
        ListInsert(stack, Before);
    }
    else
    {
         ListInsert(Convert, GetNow(Original));
         LNext(Original);
    }
    ListInsert(stack, GetNow(Original));
    printf("peek: %d\n", PeekStack(stack));
	printf("\n\n");

    /*next loop*/
    while(LNext(Original))// MainLoop
    {
        printf("\nGetNow(Otiginal): %d\n", GetNow(Original));
        
        if(IsOp(Original))
        {
            printf("\nop!\n");
            After=ConvertToOp(GetNow(Original));
            printf("aftet: %d\n", After);
            
            if(GetNow(Original)=='(')
            {
                ListInsert(stack, GetNow(Original));
            }
            
            else if(GetNow(Original)== ')' )
            {
                while('(' != PeekStack(stack))
                {
                   
                    printf("\tpop! is :%c\n", PeekStack(stack));
                    ListInsert(Convert, PopStack(stack));
                }
                PopStack(stack);

            }// end bracket
            else
            {
                Before=ConvertToOp(PeekStack(stack));
                printf("\t\tbefore:%d after:%d\n", Before, After);
				printf("IsBigOp: %d\n", IsBigOp(Before, After));

                while(!IsBigOp(Before, After)&& (!IsEmptyList(stack)) )
                {
                    Before=ConvertToOp(PeekStack(stack));
                    printf("%c type is Pop!\n", PeekStack(stack));
                    printf("\tConvert\n");
                    ListInsert(Convert, PopStack(stack));
                }
                
				//printf("a\n");
				//printf("Is %c\n", GetNow(Original));
                ListInsert(stack, GetNow(Original));   
            }// end of else
            
        }// end of if(IsOp(Original))

        else
        {
            printf("\nnum!\n");
            printf("now is %d\n", Original->now);
            ListInsert(Convert, GetNow(Original));
        }
        
    }// end of while(LNext(Original))
    
    while(!IsEmptyList(stack))// last calculate.(all of pop stack)
    {
        printf("\nloop Finish\n");
        printf("Stack: %d, %d\n", stack->now, stack->Count);
        printf("stack type is %c\n", PeekStack(stack));
        ListInsert(Convert, PopStack(stack));
    }
    printf("Finish!\n\n\n\n\n");
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
    if(Before<New)
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
    if(list->Arr[list->now]>='0' && list->Arr[list->now]<= '9')
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


