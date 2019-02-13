#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int i, j, k;
	
	for(i=0; i<9; i++)
	{
		for(j=9; j>i; j--)//°ø ¹é 
		{
			printf(" ");
		}
		
		for(k=0; k<i+1; k++)// º° 
		{ 
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
