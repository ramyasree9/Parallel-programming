#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
pthread_mutex_t sum_mutex =PTHREAD_MUTEX_INITIALIZER;
int sum=0;
void *add(void * i)
{
	pthread_mutex_lock(&sum_mutex);
	int a=(int )i;
	sum=sum+a;
	pthread_mutex_unlock(&sum_mutex);
	return NULL;
}
int main(int argc,char *argv[])
{	
	int i,r;
	pthread_t *thread;
	if(argc<2)
	{
		printf("provide sufficient arguments");
		exit(-1);
	}	
	int np=atoi(argv[1]);
	thread =(pthread_t *)malloc(np*sizeof(pthread_t));
	for(i=0;i<np;i++)
	{
		r=pthread_create(&thread[i],NULL,add,(void *)(i+1));
		if(r==1)
		{
			printf("cannot create threads");
			abort();
		}
	}
	for(i=0;i<np;i++)
	{
		r=pthread_join(thread[i],NULL);
		if(r==1)
		{
			printf("cannot join threads");
			abort();
		}
	}
	printf("resulant sum is %d",sum);
	
}

