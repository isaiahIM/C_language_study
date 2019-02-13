#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char
#define BOOL unsigned char
#define MSB 1
#define LSB 0
#define RIGHT 1
#define LEFT 0

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void PrintByte(BYTE print);
BYTE Shift(BYTE shift, int count, BOOL dir);
BYTE Mask(BYTE byte, BOOL type);

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

	BYTE val[2][8];
	int cnt=0, i;
	BOOL index;
	
	for(i=0; i<8; i++)
	{
		val[0][i] = Fnd[2][i];
		val[1][i] = 0;
	}
	
	while(1)
	{
		if(cnt==8)
		{
			Sleep(1000);
			cnt=0;
			system("cls");
		}
	
		PrintByte(val[0][cnt]);
		printf(" ");
		PrintByte(val[1][cnt]);
	
		val[1][cnt]|= Shift(Mask(val[0][cnt], LSB), 7, RIGHT);
		val[0][cnt]|= Shift(Mask(val[1][cnt], LSB), 7, RIGHT);
		
		for(i=0; i<2; i++)
		{
			val[i][cnt]=Shift(val[i][cnt], 1, LEFT);
		}
		printf("\n");
		
		cnt++;
	}
	
	return 0;
}


BYTE Shift(BYTE shift, int count, BOOL dir)
{	
	if(dir)// 좌측 시프트 
	{
		shift<<= count;
	}
	
	else// 우측 시프트 
	{
		shift>>= count;
	}
	
	return shift;
}

BYTE Mask(BYTE byte, BOOL type)
{
	BYTE MaskBit;
	
	if(type)// 최상위 비트 추출 
	{
		MaskBit = 0x80;		
		byte&=MaskBit;
	}
	
	else// 최하위 비트 추출 
	{
		MaskBit = 0x01;
		byte&=MaskBit;
	}
	
	return byte;
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

