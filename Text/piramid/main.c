#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, k, first=4, last=4;
	
	for(i=0; i<13; i++)//for�� 2�� ��� 
	{
		if(i%2!=1)
		{
			for(j=0; j<(i/2)+1; j++)
			{
				printf("*");	
			}
		}
		printf("\n");
	}
	
	printf("\n\n\n");
	
	
	for(i=0; i<9; i++)//for�� 3�� �̿� 
	{
		if(i%2!=1)
		{
			for(j=0; j<4-(i/2); j++)
			{
				printf(" ");
			}
			
			for(k=0; k<i+1; k++)
			{
				printf("*");
			}
		}
		printf("\n");
	}
	
	printf("\n\n\n");
	
	
	for(i=0; i<9; i++) //for�� 2��, ���ǹ� ��� 
	{
		if(i%2!=1)
		{
			for(j=0; j<9; j++)
			{
				if((j>=first)&&(j<=last))//�� ���� ���� ���� 
				{
					printf("*");
				}
				
				else
				{
					printf(" ");
				}
			}
			first--;
			last++;
		}
		printf("\n");
	}
	return 0;
}
