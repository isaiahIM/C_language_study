#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "CalcList.h"
#include "calc.h"
/*
typedef struct DEQUE_LIST
{
    Data Arr[ArrSize];
    int Count;
    int now;
    
    double Result;
} List;

char GetKey(void);

Data ConvertToDigit(List *list);

int ConvertToInt(char num);
int ChkCalcOp(char key);// checking calculate Arithmetic

int IsNum(List *list);
int IsOp(List *list);
int IsToken(List list);

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
int main(int argc, char *argv[])
{
    List list, PostFix, Stack;
    char key;
    int val, Buffer=0, First=1;
    double Result;
    
    InitList(&list);
    InitList(&PostFix);
    InitList(&Stack);
    
    LFirst(&PostFix);
    LFirst(&list);
    LFirst(&Stack);
    
    while(1)
    {
        key=GetKey();
        printf("%c", key);
        
        if(key>=48 &&key<=57)
        {
           Buffer*=10;
           Buffer+=ConvertToInt(key);
        }
        
        else
        {
            if(key== '=')
            {
                if(Buffer!=0)
                {
                    ListInsert(&list, Buffer);
                }
                printf("\n\n");
                break;
            }
            
            else if(CkhCalcOp(key))
            {   
                if(Buffer!=0)
                ListInsert(&list, Buffer);
                ListInsert(&list, key);
                Buffer=0;
            }// calcable key check
        }// operator check
        
    }// end of while
    
    
    printf("\n\n\n\n\n\n");
    PrtList(&list);
    
    ConvertToPostFix(&list, &PostFix, &Stack);
    printf("\n\n<PostFix>\n");
    PrtList(&PostFix);
    
    CalculatePostFix(&PostFix);
    Result= GetResult(&PostFix);
    printf("\n\n\n\n\t\t\t\t\tResult: %lf\n", Result);
    

    getch();	
  return 0;
}
