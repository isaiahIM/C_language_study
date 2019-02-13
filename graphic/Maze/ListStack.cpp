#include "ListStack.h"
/*
ListStack.h Reference:
            
typedef struct _Stack_List
{
    struct _Position *head;
    int Count;
} Stack;

typedef struct _Position
{
    int x;
    int y;
    struct _Position *next;
} Pos;

void InitStack(Stack *stack);

int GetCount(Stack *stack);
int IsEmptyStack(Stack *stack);
int ClonePos(const Pos *Original, Pos *Clone);
int PrtStack(Stack *stack);

Pos *PushStack(Stack *stack, Pos PushData);
Pos *PopStack(Stack *stack);
Pos *PeekStack(Stack *stack);
*/

void InitStack(Stack *stack)
{
    stack->Count=0;
    stack->head=NULL;
}

void ClonePos(const Pos *Original, Pos *Clone)
{
    Clone->x= Original->x;
    Clone->y= Original->y;
}

void PrtPos(Pos *pos)
{
    printf("(%d, %d)\n", pos->x, pos->y);
}

void PopStack(Stack *stack)
{
    Pos *Remove;
    Remove= PeekStack(stack);
    
    stack->head= Remove->next;
    
    free(Remove);
    stack->Count--;
}


int IsEmpty(Stack *stack)
{
    if(stack->head==NULL)
    {
        return TRUE;
    }
    return FALSE;
}

int GetCount(Stack *stack)
{
    return stack->Count;
}

int CompPos(Pos *stack1, Pos *stack2)
{
    if( (stack1->x==stack2->x) && (stack1->y==stack2->y) )
    {
        return TRUE;
    }
    return FALSE;
}

int LFirst(Stack *stack)
{
    if(!IsEmpty(stack) )
    {
        stack->now=stack->head;
        return TRUE;
    }
    return FALSE;
}

int LNext(Stack *stack)
{
    if(stack->now->next!=NULL)
    {
        stack->now=stack->now->next;
        return TRUE;
    }
    
    return FALSE;
}


Pos *PushStack(Stack *stack, Pos pos)
{
    Pos *NewNode;
    
    NewNode= (Pos*)malloc(sizeof(Pos));
    
    ClonePos(&pos, NewNode);
    
    if( IsEmpty(stack) )
    {
        stack->head=NewNode;
        NewNode->next=NULL;
    }
    else
    {
        NewNode->next=stack->head;
        stack->head=NewNode;
    }
    
    stack->Count++;
    
    return stack->head;
}

Pos *PeekStack(Stack *stack)
{
    if( !IsEmpty(stack) )
    {
        return stack->head;
    }
    return FALSE;
}


Pos SetPos(int x, int y)
{
    Pos pos;
    
    pos.x=x;
    pos.y=y;
    
    return pos;
}

Pos *GetNow(Stack *stack)
{
    return stack->now;
}
