#include "ListStack.h"

/*ListStack.h structure Reference:
            
typedef struct _POSITION
{
    int x;
    int y;
    struct _POSITION *next;
} Pos;

typedef struct _LIST_STACK
{
    int Count;
    Pos *Head;
} Stack;
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
    //Clone->next= Original->next;
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

int LFirst(Stack *stack)
{
    if(!IsEmpty(stack))
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
