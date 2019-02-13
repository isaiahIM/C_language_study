#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int i, j, k;
	
	for(i=0; i<9; i++)
	{
		for(j=0; j<i; j++)// °ø¹é 
		{
			printf(" ");
		}
		
		for(k=9; k>j; k--)//º° 
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
