#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, k;
	
	for(i=0; i<10; i++)// ���  
	{
		for(j=0; j<i; j++)//���� ��ܺ� 
		{
			printf("*");
		}
		
		for(k=10; k>i; k--)//���� 
		{
			printf(" "); 
		}
		
		for(j=9; j>i; j--)//������ ��ܺ� 
		{
			printf("*");
		}
		printf("\n");
	}
	
	for(i=0; i<10; i++)// �ϴ� 
	{
		for(k=10; k>i; k--)//���� 
		{
			printf(" "); 
		}
		
		for(j=0; j<i; j++)//���� �ϴܺ� 
		{
			printf("*");
		}
		
		for(k=0; k<i+1; k++)//������ �ϴ� ���� 
		{
			printf(" "); 
		}
		
		for(j=9; j>i; j--)//������ �ϴܺ� 
		{
			printf("*");
		}
		
		printf("\n");
	}
	return 0;
}
