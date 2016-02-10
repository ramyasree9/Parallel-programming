#include<stdio.h>
#define us 1000000
#include<stdlib.h>
#include<sys/time.h>
#include<omp.h>
int main(int argc,char *argv[])
{
	struct timeval start,end;
	int i,j,k;
	if(argc!=4)
	{
 		printf("provide sufficient arguments");
		exit(-1);
	}
	int Mat_rows=atoi(argv[1]);
	int Mat_cols=atoi(argv[2]);
	int Vect_size=atoi(argv[3]);
	if(Mat_cols!=Vect_size)
	{
		printf("cant  multiply");
		exit(-1);
	}
	double **Matrix,*Vector,*Result;	
	Matrix =(double **)malloc(Mat_rows*sizeof(double *));
	if(Matrix==NULL)
	{
		printf("mem not available");
		exit(-1);
	}
	for(i=0;i<Mat_rows;i++)
	{
		Matrix[i]=(double *) malloc(Mat_cols*sizeof(double));
	}
	for(i=0;i<Mat_rows;i++)
	{
		for(j=0;j<Mat_cols;j++)
		{
			Matrix[i][j]=rand();
		}
	}
	Vector=(double *)malloc(Vect_size*sizeof(double));
	if(Vector==NULL)
	{
		printf("memory not available");
		exit(-1);
	}
	for(i=0;i<Vect_size;i++)
	{
		Vector[i]=rand();
	}
	Result=(double *)malloc(Mat_rows*sizeof(double));
	if(Result==NULL)
	{
		printf("memory not available");
		exit(-1);
	}
	gettimeofday(&start,NULL);
//	printf("%f : %f ",(double)start.tv_usec,(double)start.tv_sec);
	#pragma omp parallel for private(j)
	for(i=0;i<Mat_rows;i++)
	{
		for(j=0;j<Mat_cols;j++)
		{
			Result[i]=Result[i]+(Matrix[i][j]*Vector[j]);	
		}
	}
	gettimeofday(&end,NULL);
//	printf("\n %f : %f ",(double )end.tv_usec,(double )end.tv_sec);
/*	printf("resultant veotor is:\n");
	for(i=0;i<Mat_rows;i++)
	{
		printf("%lf\n",Result[i]);
	}*/
//	start.tv_usec=(start.tv_sec*us)+start.tv_usec;
//	end.tv_usec=end.tv_usec+(end.tv_sec*us);
	double time_taken=(double)(((end.tv_sec*us)+(end.tv_usec))-(start.tv_usec+(start.tv_sec*us)))/us;
	printf("time taken is :%f\n",time_taken);
	printf("no of operations: %d\n",(2*Mat_rows*Vect_size));
	printf("performance is : %f\n",((2*Mat_rows*Vect_size)/(time_taken*us)));
	free(Matrix);
	free(Vector);
	free(Result);
}
