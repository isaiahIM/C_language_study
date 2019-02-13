#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, k, cnt=4, index=1;
	
	for(i=0; i<18; i++)
	{
		if(i%2!=0)
		{
			
			for(j=0; j<cnt; j++)// °ø¹é 
			{
				printf(" ");
			}
			
			for(k=0; k<index; k++)//º° 
			{
				printf("*");
			}
			if(i<9)
			{
				cnt--;
				index+=2;
			}
			else
			{
				cnt++;
				index-=2;
			}
		}
		
		printf("\n");
	}
	return 0;
}
