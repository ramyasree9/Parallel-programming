#include<stdio.h>
#include<omp.h>
int main()
{
	int a=10;
	omp_set_num_threads(4);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			a=20;
			printf("%d\n",a);	
		}
		#pragma omp section
		{
			a=30;
			printf("%d\n",a);
		}
	}
}
