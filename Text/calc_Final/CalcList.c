#include <Windows.h>
#include "CalcList.h"
#include "calc.h"
/*

typedef struct DEQUE_LIST
{
    ArrType Arr[ArrSize];
    int Count;
    int now;
    
    double Result;
} List;

void InitList(List *list);

void PushStack(List *list, Data data);
void PushQueue(List *list, Data data);

void PrtList(List *list);
Data RemoveList(List *list);

void SetToken(List *list, int state);

Data PopStack(List *list);
Data PeekStack(List *list);

Data PopQueue(List *list);
Data PeekQueue(List *list);

int IsEmptyList(List *list);

int LFirst(List *list);
int LNext(List *list);
int LPrev(List *list);
int Llast(List *list);
*/

void InitList(List *list)
{   
    list->Count=0;
    list->now=-1;
    list->Result=0;
}

void ListInsert(List *list, Data data)
{
    list->Count++;
    list->now+=1;
    list->Arr[list->now]=data;
    printf("\n%d is Insert! now: %d, count is %d\n", list->Arr[list->now], list->now, list->Count);
    printf("After now: %d\n", list->now);
}

void PrtList(List *list)
{
    LFirst(list);
    
    if(IsOp(list))
    {
        printf("Arr[%d]: %c\n", list->now, list->Arr[list->now]);
    }
    else
    {
        printf("Arr[%d]: %d\n", list->now, list->Arr[list->now]);
    }
    
    
    while(LNext(list))
    {
        if(IsOp(list))
        {
            printf("Arr[%d]: %c\n", list->now, list->Arr[list->now]);
        }
        else
        {
            printf("Arr[%d]: %d\n", list->now, list->Arr[list->now]);
        }
    }
}


Data PopStack(List *list)
{
    Data Remove;
    
	if (IsEmptyList(list))
	{
		printf("can't PopStack Function. list is empty!!\n");
		return FALSE;
	}
	
	Llast(list);
	Remove = list->Arr[list->now];
    list->Count--;
    list->now--;
    
	
    return Remove;
}

Data PeekStack(List *list)
{
    if(IsEmptyList(list))
    {
        printf("can't PeekStack Function. list is empty!!\n");
        return FALSE;
    }
    
    Llast(list);
	
    printf("Peek Now: %d, Count: %d\n", list->now, list->Count);
    return list->Arr[list->now];
}

Data GetNow(List *list)
{
    return list->Arr[list->now];
}

Data RemoveList(List *list)
{
    Data Remove, now;
    now=list->now;
    Remove=GetNow(list);
    
    while(now!=list->Count)
    {
        //printf("\t\tRemove: %c, RemoveBackup: %c\n", list->Arr[now], list->Arr[now+1]);
        list->Arr[now]=list->Arr[now+1];
        now+=1;
        //Sleep(1000);
        //printf("now: %d\n", now);
    }
    
    list->now-=1;
    list->Count--;
    
    return Remove;
}

int IsEmptyList(List *list)
{
    if(list->Count==0)
    {
        return TRUE;
    }
    
    return FALSE;
}

int LFirst(List *list)
{
    if(!IsEmptyList(list))
    {
        list->now=0;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int LNext(List *list)
{
    int cnt= list->Count;
    if(!IsEmptyList(list) && list->now!=cnt-1)
    {
        list->now=list->now+1;
        cnt= list->Count;
        
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int LPrev(List *list)
{
    if(!IsEmptyList(list) && list->now!=0)
    {
        list->now=list->now-1;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int Llast(List *list)
{
    if(!IsEmptyList(list))
    {
        list->now=list->Count-1;
        
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


double GetResult(List *list)
{
    return list->Result;
}

double WriteResult(List *list, Data data)
{
    list->Result=data;
    return list->Result;
}
