#ifndef _LIST_BASED_STACK_H
#define _LIST_BASED_STACK_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _POSITION
{
    int x;
    int y;
    struct _POSITION *next;
} Pos;

typedef struct _LIST_STACK
{
    int Count;
    Pos *head;
    Pos *now;
} Stack;


void InitStack(Stack *stack);
void ClonePos(const Pos *Original, Pos *Clone);
void PrtPos(Pos *pos);
void PopStack(Stack *stack);


int IsEmpty(Stack *stack);
int GetCount(Stack *stack);

int LFirst(Stack *stack);
int LNext(Stack *stack);
int Equal(Pos pos1, Pos pos2);

Pos *PushStack(Stack *stack, Pos pos);
Pos *PeekStack(Stack *stack);
Pos SetPos(int x, int y);

#endif
