#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Swap(int *a, int *b);// 함수 정의 

int main(int argc, char *argv[]) {
	
	int i, j, k, Switch=1, first=0, last=15;
	
	while(1)
	{
		i=first;
		while(i+1!=last)
		{
			if(i<5)//별 생성 
			{
				for(j=0; j<i; j++)
				{
					printf("*");
				}
			}
			
			else if((i>=5)&&(i<10))//별 이동 
			{			
				for(j=i; j>=5; j--)
				{
					printf(" ");
				}
				for(k=0; k<5; k++) 
				{
					printf("*");
				}
			}
			
			
			else//별 제거		 
			{
				for(j=4; j<i; j++)
				{
					printf(" ");
				}
				
				for(k=i+1; k<15; k++)
				{
					printf("*");
				}
			}
			
			Sleep(100); 
			system("cls");
			i+=Switch;
		}
				
		Switch*=-1;
		Swap(&first, &last);
	}
	
	return 0;
}

void Swap(int *a, int *b)//함수 선언 
{
	int cmp;
	
	cmp=*a;
	*a=*b;
	*b=cmp;
}
