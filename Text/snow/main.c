#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i, j, space=5, k, half_i;
	
	for(i=0; i<10; i++)
	{
		half_i=i%2;
		
		if(half_i==0)
		{
			for(j=0; j<space/2; j++)
			{
				printf(" ");
			}
		}
		
		else
		{
			for(j=0; j<space; j++)
			{
				printf(" ");
			}
		}
		
		for(k=0; k<5; k++)
		{
			printf("*");
			
			for(j=0; j<space; j++)
			{
				printf(" ");
			}
		}
		
	printf("\n");	
	}//우왕!! 눈이다!!!!! 밖에 나가면 커플들이 있겠지? 커플들 죽었으면.. 
	return 0;
}
