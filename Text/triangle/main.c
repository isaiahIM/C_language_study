#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, k;
	
	for(i=0; i<9; i++)
	{
		if(i%2!=1)
		{
			for(j=0; j<4-(i/2); j++)//ฐ๘น้ 
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
	return 0;
}
