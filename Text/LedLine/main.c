#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int i, j=5;
	
	while(1)
	{
		for(i=0; i<5; i++)// ÀüÁø 
		{
			printf("*");
			Sleep(500);
		}
		system("cls");
		
		for(i=0; i<5; i++)
		{
			for(j=5; j>i; j--)
			{
				printf("*");
			}
			Sleep(500);
			system("cls");
		}
	}
		 	
	return 0;
}
