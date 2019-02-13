#ifndef _LIST_STACK_H
#define _LIST_STACK_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _Stack_List
{
    struct _Position *head;
    struct _Position *now;
    
    int Count;
    
} Stack;

typedef struct _Position
{
    int x;
    int y;
    struct _Position *next;
} Pos;

void InitStack(Stack *stack);
void PopStack(Stack *stack);
void ClonePos(const Pos *Original, Pos *Clone);
void PrtPos(Pos *pos);

int GetCount(Stack *stack);
int IsEmptyStack(Stack *stack);
int PrtStack(Stack *stack);
int CompPos(Pos *stack1, Pos *stack2);

int LFirst(Stack *stack);
int LNext(Stack *stack);


Pos *PushStack(Stack *stack, Pos PushData);
Pos *PeekStack(Stack *stack);

Pos *GetNow(Stack *stack);
Pos SetPos(int x, int y);

#endif
