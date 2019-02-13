#include <Windows.h>
#include "CalcList.h"
#include "calc.h"
#define DEBUG 0// select Debugging mode



void InitList(List *list)
{   
    list->Arr[0]= '\0';
    list->Count=0;
    list->now=-1;
    list->Result=0;
}

void ListInsert(List *list, Data data)
{
    list->Count++;
    list->now+=1;
    list->Arr[list->now]=data;
    if(DEBUG)
    {
        printf("\n%d is Insert! now: %d, count is %d\n", list->Arr[list->now], list->now, list->Count);
        printf("After now: %d\n", list->now);
    }
}

void PrtList(List *list)
{
    LFirst(list);
    
    if(IsOp(list))
    {
        printf("%c ", list->Arr[list->now]);
    }
    else
    {
        printf("%d ", list->Arr[list->now]);
    }
    
    
    while(LNext(list))
    {
        if(IsOp(list))
        {
            printf("%c ", list->Arr[list->now]);
        }
        else
        {
            printf("%d ", list->Arr[list->now]);
        }
    }
    printf("\n\n\n");
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
	
    if(DEBUG)
	{
        printf("Peek Now: %d, Count: %d\n", list->now, list->Count);
    }
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
        list->Arr[now]=list->Arr[now+1];
        now+=1;
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

double WriteResult(List *list, double data)
{
    list->Result=data;
    return list->Result;
}
