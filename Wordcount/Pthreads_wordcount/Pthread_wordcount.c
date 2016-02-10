#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#define buflen 1000
struct node
{
 	char *word;
	int count;
	struct node *next;
}*Words[26]; 
int part_len;
void init();
void parse(char *s,int start,int end);
void create(char *s);
void* fun(void* r)
{
	printf("s\n");
	int rank=(int)r;
	int start,end;
	FILE *fp;
	int i;
	char s[buflen];
	init();
	start=(rank*part_len);
	end=(start+part_len-1);
	if(end>25)
	end=25;
	fp=fopen("Input-word-count.txt","r");
	while(fgets(s,buflen-1,fp))
	{
	 	if (s[strlen(s) - 1] == '\n')
		s[strlen(s)-1] = '\0';
		char* new_line = (char *)malloc(sizeof(char)*(strlen(s) + 1));
		strcpy(new_line, s);
		parse(new_line,start,end);
	}
/*	for(i=start;i<=end;i++)
	{
	struct node *L;     
	L=Words[i];
	while(L!=NULL)
	{
		printf("%s  : %d\n",L->word,L->count);
		L=L->next;
	}
	}*/
	pthread_exit(NULL);
	return NULL;	
}
void init()
{
int i;
for(i=0;i<26;i++)
Words[i]=NULL;
}
void create(char *s)
{
	int k=s[0]-97;
	if(Words[k]==NULL)
	{
		struct node *L;
		L=(struct node *)malloc(sizeof(struct node *));
		L->word=(char *)malloc(sizeof(char )*(strlen(s)+1));
		strcpy(L->word,s);
		L->count=1;
		L->next=NULL;
		Words[k]=L;
	}
	else
	{
	        struct node *L=Words[k];
		struct node *prev;
		while(L!=NULL)
		{
			if(!strcmp((L->word),s))
			{
				L->count++;
				return;
			}
			prev=L;
			L=L->next;
		}
		struct node *N;
		N=(struct node *)malloc(sizeof(struct node *));
		N->word=(char *)malloc(sizeof(char )*(strlen(s)+1));
		strcpy(N->word,s);
		N->count=1;
		N->next=NULL;
		prev->next=N;
	}
}
void parse(char *s,int start,int end)
{
	int i,len=strlen(s),index=0,k;
	char *temp;
	for(i=0;i<=len;i++)
	{
		if((s[i]=='\0')||(s[i]=='\n')||(s[i]==' '))
		{
			temp=(char *)malloc(sizeof(char )*(i-index+1));
			strncpy(temp,s+index,(i-index));
			k=temp[0]-97;
			if((k>=start) && (k<=end))
			{
				create(temp);
			}
		index=i+1;
		}
	}
}
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("provide sufficient arguments <num of threads>");
		exit(-1);
	}
	int num=atoi(argv[1]),ret;
	printf("no of threads : %d",num);
	 part_len=26/num;
	if(26%num) part_len++;
	printf("part len is:  %d",part_len);
	int i;
	pthread_t Thread[num];
	for(i=0;i<num;i++)
	{
	//	printf("going to create");
		ret=pthread_create(&Thread[i],NULL,fun,(void *)i);
		if(ret)
		{
			printf("thread creation failed");
			exit(-1);
		}
	}
	for(i=0;i<num;i++)
	{
	pthread_join(Thread[i],NULL);
	}
	for(i=0;i<num;i++)
	{
		ret=pthread_create(&Thread[i],NULL,print,(void *)i);
		if(ret)
		{
			printf("thread creation failed");
			exit(-1);
		}
	}
}
