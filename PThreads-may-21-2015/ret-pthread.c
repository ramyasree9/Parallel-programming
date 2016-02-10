#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
// int a[5]={1,2,3,4,5};

void * fun(void *d)
{		
//	int a[5]={1,2,3,4,5};
	return (void *)23;
} 
int main(int argc,char *argv[])
{
	int *c=23;
	*c=40;
	void **status;
	int i;
	pthread_t thread;
	pthread_create(&thread,NULL,fun,NULL);
	pthread_join(thread,&status);
//	int *b;
//	b=(int *)malloc(sizeof(int )*5);
//	b=(int *)status;
	printf("%d",*(int*)status);
/*	for(i=0;i<5;i++)
	{
	printf("%d \n",b[i]);}*/
}
