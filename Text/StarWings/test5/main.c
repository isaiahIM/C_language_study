#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, k;
	
	for(i=0; i<10; i++)// 상단  
	{
		for(j=0; j<i; j++)//왼쪽 상단별 
		{
			printf("*");
		}
		
		for(k=10; k>i; k--)//공백 
		{
			printf(" "); 
		}
		
		for(j=9; j>i; j--)//오른쪽 상단별 
		{
			printf("*");
		}
		printf("\n");
	}
	
	for(i=0; i<10; i++)// 하단 
	{
		for(k=10; k>i; k--)//공백 
		{
			printf(" "); 
		}
		
		for(j=0; j<i; j++)//왼쪽 하단별 
		{
			printf("*");
		}
		
		for(k=0; k<i+1; k++)//오른쪽 하단 공백 
		{
			printf(" "); 
		}
		
		for(j=9; j>i; j--)//오른쪽 하단별 
		{
			printf("*");
		}
		
		printf("\n");
	}
	return 0;
}
