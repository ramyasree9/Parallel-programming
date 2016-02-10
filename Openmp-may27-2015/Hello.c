#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
int main()
{
int id;
printf("before");
omp_set_num_threads(5);
#pragma omp parallel private(id)
{	
id=omp_get_thread_num();
printf("hello world %d \n",id);
exit(-1);
printf("nhb");
}
printf("after");
}
