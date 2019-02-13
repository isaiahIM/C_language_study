#ifndef CALC_LIST_H

#define CALC_LIST_H

#define TRUE 1
#define FALSE 0

#define ArrSize 100

#include<stdio.h>

typedef char Data;

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

Data GetNow(List *list);

int IsEmptyList(List *list);

int LFirst(List *list);
int LNext(List *list);
int LPrev(List *list);
int Llast(List *list);

double WriteResult(List *list, Data data);
double GetResult(List *list);

#endif
