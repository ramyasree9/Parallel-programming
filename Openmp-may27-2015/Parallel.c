#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int main(int argc,char *argv[])
{
	int i,j;
	#pragma omp parallel for private(j)
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{	
		int id=omp_get_thread_num();
		printf("id is %d :  %d , %d \n",id,i,j);
		}
	}
}
