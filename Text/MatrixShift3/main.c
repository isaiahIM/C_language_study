#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char
#define BOOL unsigned char
#define MSB 0x80
#define LSB 0x01
#define RIGHT 0
#define LEFT 1
#define DIGIT 5

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void PrintByte(BYTE print);// 1바이트 출력하는 함수 
void Matrix_init(int *count);// 초기화 함수 
BYTE Shift(BYTE shift, int count, BOOL dir);// 시프트 함수 (시프트할 바이트, 시프트 횟수, 방향) 
BYTE Mask(BYTE byte, BOOL MaskBit);// 특정 비트를 추출하는 함수 

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

	BYTE val[DIGIT][8];
	int cnt=0, i, j, flag=0;
	BOOL index;
	
	for(j=0; j<DIGIT; j++)// 메트릭스 초기화 
	{
		for(i=0; i<8; i++)
		{
			val[j][i] = 0;
		}
	}

	
	while(1)
	{
		if(flag%8==0)
		{
			if((flag/8)>9)
			{
				flag=0;
			}
			
			for(i=0; i<8; i++)
			{
				val[0][i] = Fnd[(int)(flag/8)][i];
			}
		}
		
		if(cnt==8)// 초기화 
		{
			Matrix_init(&cnt);
			flag++;
		}
	
		for(i=0; i<DIGIT; i++)// 매트릭스 출력 
		{
			PrintByte(val[i][cnt]);
			printf(" ");
		}

		for(i=0; i<DIGIT; i++)// 다음 자리에 도트를 넘겨주는 함수 
		{
			j=i+1;
			if(j==DIGIT)
			{
				j=0;
			}
			
			val[j][cnt]|= Shift(Mask(val[i][cnt], LSB), 7, LEFT);// 최하위 비트를 옆자리 최상위 비트로 넘겨줌 
		}
		
		for(i=0; i<DIGIT; i++)// 시프트 하는 함수 
		{
			val[i][cnt]=Shift(val[i][cnt], 1, RIGHT);
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

BYTE Mask(BYTE byte, BOOL MaskBit)
{
	
	return MaskBit&byte;
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

void Matrix_init(int *count)
{
	Sleep(1000);
	*count=0;
	system("cls");
}

