#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void * print(void * msg)
{
	int i;
	i=(int )msg;
	printf("hello thread %d\n",i);
	pthread_exit(NULL);
	return NULL;
}
int main(int argc,char *argv[])
{
	int i,r;
	pthread_t thread[5];
	for(i=0;i<5;i++)
	{	
		r=pthread_create(&thread[i],NULL,print,(void *)i);
		if(r==1)
		{
			printf("thread creation failed");
			abort();
		}
	}
	printf("hello main\n");
	pthread_exit(NULL);
}
