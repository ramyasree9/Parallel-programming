#include<stdio.h>
#include<omp.h>
int main()
{
	int i,j;
	int n=12,t=1,arr[12];
	omp_set_num_threads(4);
	#pragma omp parallel for schedule(static) ordered
	for(i=0;i<n;i++)
	{
	#pragma omp ordered
  		arr[i]=t;
		int id=omp_get_thread_num();
		printf("%d :%d : %d\n",id,i,arr[i]);
//	#pragma omp ordered
		t=t*2;
	}
	
	for(i=0;i<12;i++)
	printf("%d\n",arr[i]);
}
