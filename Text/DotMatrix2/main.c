#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char
#define BOOL unsigned char
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void PrintByte(BYTE print);
BYTE Shift(BYTE shift, BOOL dir);
void Clear(int *num);

int main(int argc, char *argv[]) {
	
	BYTE Fnd[10][8]=
	{
		{0x00, 0x38, 0x44, 0x4c, 0x54, 0x64, 0x44, 0x38},// 0
		{0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c},// 1
		{0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c},// 2
		{0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38},// 3
		{0x00, 0x08, 0x18, 0x28, 0x48, 0x7c, 0x08, 0x08},// 4
		{0x00, 0x7c, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38},// 5
		{0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38},// 6
		{0x00, 0x7c, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20},// 7
		{0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38},// 8
		{0x00, 0x38, 0x44, 0x44, 0x3c, 0x04, 0x44, 0x38},// 9
	};

	BYTE val[8];
	int cnt=0, i;
	
	for(i=0; i<8; i++)
	{
		val[i]=Fnd[2][i];
	}
	
	while(1)
	{
		if(cnt==8)
		{
			Sleep(500);
			Clear(&cnt);
			system("cls");
		}
		
		PrintByte(val[cnt]);
		val[cnt]=Shift(val[cnt], 0);
		printf("\n");
		
		cnt++;
	}
	return 0;
}


void PrintByte(BYTE print)
{
	int i;
	BYTE ChkBit=0x80;
	
	for(i=0; i<8; i++)
	{	
		if(print&(ChkBit>>i))
		{
			printf("*");
		}
		
		else
		{
			printf("-");
		}
	}
}

BYTE Shift(BYTE shift, BOOL dir)
{
	BYTE MaskBit, MaskVal=0x00;
	
	if(dir)// 좌측 시프트 
	{
		MaskBit = 0x80;
		
		MaskVal = (shift&MaskBit);
		MaskVal>>= 7;
		
		shift<<= 1;
		shift|= MaskVal;
	}
	
	else// 우측 시프트 
	{
		MaskBit = 0x01;
		
		MaskVal = (shift&MaskBit);
		MaskVal<<= 7;
		
		shift>>= 1;
		shift|= MaskVal;
	}
	
	return shift;
}

void Clear(int *num)
{
	*num=0;
}












