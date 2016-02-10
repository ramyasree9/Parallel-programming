#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
struct data
{
	int a;
	char st[20];
};
void * print(void * msg)
{
	struct data *d;
	d=(struct data *)msg;
	printf("hello thread %d %s\n",d->a,d->st);
	pthread_exit(NULL);
	return NULL;
}
int main(int argc,char *argv[])
{
	int i,r;
	pthread_t thread;
//	for(i=0;i<5;i++)
	{	struct data d;
		d.a=1;
		sprintf(d.st,"its me");
		r=pthread_create(&thread,NULL,print,(void *)&d);
		if(r==1)
		{
			printf("thread creation failed");
			abort();
		}
	}
	printf("hello main\n");
	pthread_exit(NULL);
}
