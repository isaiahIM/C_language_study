#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, k, number=0;
	char num[10][8]=
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
	
	while(1)
	{
		if(number>9)
		{
			number=0;
		}
		for(k=0; k<10; k++)//���� ��ü 
		{
			for(i=0;i<8;i++)//���� ��� 
			{
				for(j=0;j<8;j++)//10�� �ڸ� ��Ʈ 
				{
					if( num[number][i]& (0x80 >> j) )
					{
						printf("*");
					}
					
					else
					{
						printf(" ");	
					}
				}
				
				for(j=0;j<8;j++)//�����ڸ� ��Ʈ 
				{
					if( num[k][i]& (0x80 >> j) )
					{
						printf("*");
					}
					
					else
					{
						printf(" ");	
					}
				}
				printf("\n");
			}
			
			Sleep(500);
			system("cls");
		}
		number++;
	} 	
	return 0;
}