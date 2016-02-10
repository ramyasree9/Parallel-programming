#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#define ns 1000000
pthread_mutex_t mutexvar=PTHREAD_MUTEX_INITIALIZER;
int Matrix_rows,Matrix_cols,Vector_size;	
double **Matrix,*Vector,*Result_matrix;
void * mul(void *l)
{
	int j;
	double sum=0;
	int a=(int)l;
//	printf("\n%d\n",a);
	for(j=0;j<Vector_size;j++)
		sum=sum+(Matrix[a][j]*Vector[j]);
	pthread_mutex_lock(&mutexvar);
	Result_matrix[a]=sum;
	pthread_mutex_unlock(&mutexvar);
	return NULL;
}
int main(int argc,char *argv[])
{
	int i,j,r;
	struct timeval start,end;
	double Time_taken;
	if(argc<3)
	{
		printf("provide matrix and vector sizes");
		exit(0);
	}
	Matrix_rows=atoi(argv[1]);
	Matrix_cols=atoi(argv[2]);
	Vector_size=atoi(argv[3]);
	printf("matrix n vector size %d %d %d",Matrix_rows,Matrix_cols,Vector_size);
	Matrix=(double **)malloc(sizeof(double *)*Matrix_rows);
	if(Matrix==NULL)
	{
		printf("memory not available");
		exit(0);
	}
	for(i=0;i<Matrix_rows;i++)
	{
		Matrix[i]=(double * )malloc(sizeof(double )*Matrix_cols);	
	}
	for(i=0;i<Matrix_rows;i++)
	{
		for(j=0;j<Matrix_cols;j++)
		{
			Matrix[i][j]=rand()/100;
//			printf("\n %f \n",Matrix[i][j]);
		}
	}	
	Vector=(double *)malloc(sizeof(double)*Vector_size);
	if(Vector==NULL)
	{
		printf("memory not available");
		exit(0);
	}
	for(i=0;i<Vector_size;i++)
	{
		Vector[i]=rand()/100;
//		printf("\n %f \n",Vector[i]);
	}
	Result_matrix=(double *)malloc(sizeof(double)*Matrix_rows);
	if(Result_matrix==NULL)
	{
		printf("memory not available");
		exit(0);
	}
	gettimeofday(&start,NULL);
	pthread_t thread[Matrix_rows];
	for(i=0;i<Matrix_rows;i++)
	{
		r=pthread_create(&thread[i],NULL,mul,(void *)i);
		if(r)
		{
			printf("thread creation failed");
			exit(0);
		}
	}
	for(i=0;i<Matrix_rows;i++)
	{
		r=pthread_join(thread[i],NULL);
		if(r)
		{
			printf("thread joining failed");
			exit(0);
		}
	}
	gettimeofday(&end,NULL);	
	if(end.tv_usec<start.tv_usec)
	{
		end.tv_usec=end.tv_sec+ns;
		end.tv_sec=end.tv_sec-1;
	}
	end.tv_usec=end.tv_usec-start.tv_usec;
	end.tv_sec=end.tv_sec-start.tv_sec;
	Time_taken=(double)end.tv_usec/ns;
	Time_taken=Time_taken+(double )end.tv_sec;
	printf("no of operations        : %d\n",2*Matrix_rows*Vector_size);
	printf("Time taken               : %f\n",Time_taken);
	printf("performance in Mflops is : %f\n",(2*Matrix_rows*Vector_size)/(Time_taken*ns));
//	printf("resultant matrix is:\n");
/*	for(i=0;i<Matrix_rows;i++)
	{
		printf("%f\n",Result_matrix[i]);
	}*/
}
