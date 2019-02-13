#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, Rotate;
	unsigned char Block[4][4][4]=
	{
		{	{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		}, 
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0} 
			
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
			
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
			
		}
	};
	while(1)
	{
		for(Rotate=0; Rotate<4; Rotate++)
		{
			for(i=0; i<4; i++)
			{
				for(j=0; j<4; j++)
				{
					if(Block[Rotate][i][j])
					{
						printf("*");
					}
					else
					{
						printf("-");
					}
				}
				printf("\n");
			}
			Sleep(1000);
			system("cls");
		}
	}
	
	return 0;
}
