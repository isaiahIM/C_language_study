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

void PrintByte(BYTE print);// 1����Ʈ ����ϴ� �Լ� 
void Matrix_init(int *count);// �ʱ�ȭ �Լ� 
BYTE Shift(BYTE shift, int count, BOOL dir);// ����Ʈ �Լ� (����Ʈ�� ����Ʈ, ����Ʈ Ƚ��, ����) 
BYTE Mask(BYTE byte, BOOL MaskBit);// Ư�� ��Ʈ�� �����ϴ� �Լ� 

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
	int cnt=0, i, j;
	BOOL index;
	
	for(j=1; j<DIGIT; j++)// ��Ʈ���� �ʱ�ȭ 
	{
		for(i=0; i<8; i++)
		{
			val[0][i] = Fnd[2][i];
			val[j][i] = 0;
		}
	}

	
	while(1)
	{
		if(cnt==8)// �ʱ�ȭ 
		{
			Matrix_init(&cnt);
		}
	
		for(i=0; i<DIGIT; i++)// ��Ʈ���� ��� 
		{
			PrintByte(val[i][cnt]);
			printf(" ");
		}

		for(i=0; i<DIGIT; i++)// ���� �ڸ��� ��Ʈ�� �Ѱ��ִ� �Լ� 
		{
			j=i+1;
			if(j==DIGIT)
			{
				j=0;
			}
			
			val[j][cnt]|= Shift(Mask(val[i][cnt], LSB), 7, LEFT);// ������ ��Ʈ�� ���ڸ� �ֻ��� ��Ʈ�� �Ѱ��� 
		}
		
		for(i=0; i<DIGIT; i++)// ����Ʈ �ϴ� �Լ� 
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
	if(dir)// ���� ����Ʈ 
	{
		shift<<= count;
	}
	
	else// ���� ����Ʈ 
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
	Sleep(500);
	*count=0;
	system("cls");
}
