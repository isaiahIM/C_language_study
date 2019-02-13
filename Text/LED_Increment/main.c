#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	
	int i;
	while(1)
	{
		system("cls");
		for(i=0; i<10; i++)
		{
			Sleep(500);
			printf("*");
		}
	}
	
	return 0;
}
