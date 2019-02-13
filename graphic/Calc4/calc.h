#ifndef CALC_H
#define CALC_H

#define BRACKET 1

#define PLUS 2
#define SUBSTRACT 2

#define MULTIPLEX 3
#define DIVISION 3

#include "CalcList.h"

void ConvertToPostFix(List *Original, List *Convert, List *stack);
void CalculatePostFix(List *list);
void ClearList(List *list);

char GetKey(void);

int ConvertToInt(char num);
int ConvertToOp(char key);
int IsBigOp(Data Before, Data New);
int ChkCalcOp(char key);// checking calculate Arithmetic

int IsNum(List *list);
int IsOp(List *list);
int IsToken(List *list);

#endif
