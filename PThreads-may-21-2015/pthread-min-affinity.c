#define _GNU_SOURCE;
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
const int max=1000000;
int lsize;
int min;
int b[100];
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
void * findmin(void *i)
{	
	int lmin=max;
	pthread_t me=pthread_self();
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	int kl;
	for(kl=0;kl<3;kl++)
	{
        	CPU_SET(kl,&cpuset);
	}
	pthread_setaffinity_np(me,sizeof(cpu_set_t),&cpuset);
	int start=(int )i * lsize;
	int j,k=start+lsize;
	for(j=0;j<k;j++)
	{
		if(lmin>b[j])
		lmin=b[j];
	}
	pthread_mutex_lock(&m);
	if(min>lmin)
	min=lmin;
	pthread_mutex_unlock(&m);
	return NULL;
}
int main(int argc,char *argv[])
{	
	min=max;
	int i;
	if(argc!=2)
	{
		printf("provide args");
		exit(-1);
	}
	int no=atoi(argv[1]);
	pthread_t *thread;	
	thread=(pthread_t *)malloc(sizeof(pthread_t)*no);
	lsize=100/no;
	for(i=0;i<100;i++)
	b[i]=i+2;
	for(i=0;i<no;i++)
	{
		pthread_create(&thread[i],NULL,findmin,(void *)i);
	}
	
	for(i=0;i<no;i++)
	{
		pthread_join(thread[i],NULL);
	}
	printf("%d",min);
}
