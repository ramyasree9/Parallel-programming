#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int no;
int interval;
double result=0;
pthread_mutex_t mutexvar=PTHREAD_MUTEX_INITIALIZER;
void * cal(void * a)
{
	double sum;
	int id=(int )a;
	double x=id/(double)no;
	sum=1/(1+(x*x));
	if(id>0&&id<no)
	{
		sum=2*sum;
	}
	pthread_mutex_lock(&mutexvar);
	result=result+sum;
	pthread_mutex_unlock(&mutexvar);
	return NULL;
}
int main(int argc,char *argv[])
{	
	int i,r;
	pthread_t *thread;
	if(argc<2)
	{
		printf("provide sufficient arguments");
		exit(0);
	}
	no=atoi(argv[1]);
	interval=no;
	thread =(pthread_t)malloc(sizeof(pthread_t)*(no+1));
	for(i=0;i<=no;i++)
	{
		r=pthread_create(&thread[i],NULL,cal,(void *)i);
		if(r)
		{
			printf("thread creation failed");
			abort();
		}
	}
	for(i=0;i<no;i++)
	{
		r=pthread_join(thread[i],NULL);
		if(r)
		{
			printf("thread join failed");
			abort();
		}
	}
	double pi=(result*2)/no;
	printf("value of pi is %f",pi);
	
}
