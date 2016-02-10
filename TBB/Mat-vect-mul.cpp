#include<iostream>
#define us 1000000
#include<stdlib.h>
#include<tbb/blocked_range.h>
#include<tbb/parallel_for.h>
#include<tbb/task_scheduler_init.h>
#include<tbb/tick_count.h>
using namespace std;
using namespace tbb;
double *Result;
class Mul
{
	private:
	int Mat_rows,Mat_cols,Vect_size;
	double **Matrix,*Vector;
	public:
	Mul(double **Matrix,double *Vector,int Mat_rows,int Mat_cols,int Vect_size)
	{
		this->Matrix=Matrix;
		this->Vector=Vector;
		this->Mat_rows=Mat_rows;
		this->Mat_cols=Mat_cols;
		this->Vect_size=Vect_size;
	}
	void operator () (const blocked_range<int> &r ) const
	{	
	for(int i=r.begin();i<r.end();i++)
	{
		for(int j=0;j<Mat_cols;j++)
		{
			Result[i]=Result[i]+(Matrix[i][j]*Vector[j]);	
		}
	}
	}
};
int main(int argc,char **argv)
{
	int i,j,k;
	if(argc!=5)
	{
 		printf("provide sufficient arguments <Num of threads> <Mat_rows> <Mat_cols> <Vect_size>");
		exit(-1);
	}
	int num=atoi(argv[1]);
	task_scheduler_init init(num);
	int Mat_rows=atoi(argv[2]);
	int Mat_cols=atoi(argv[3]);
	int Vect_size=atoi(argv[4]);
	printf("yess ");
	if(Mat_cols!=Vect_size)
	{
		printf("cant  multiply");
		exit(-1);
	}
	printf("heree e");
	double **Matrix,*Vector;
	 Matrix =(double **)malloc(Mat_rows*sizeof(double *));
        if(Matrix==NULL)
        {
                printf("mem not available");
                exit(-1);
        }
        for(i=0;i<Mat_rows;i++)
        {
                Matrix[i]=(double *)malloc(Mat_cols*sizeof(double ));
        }
        for(i=0;i<Mat_rows;i++)
        {
                for(j=0;j<Mat_cols;j++)
                {
                        Matrix[i][j]=rand();
                }
        }
        Vector=(double *)malloc (Vect_size*(sizeof(double)));
        if(Vector==NULL)
        {
                printf("memory not available");
                exit(-1);
        }
        for(i=0;i<Vect_size;i++)
        {
                Vector[i]=rand();
        }
        Result=(double*) malloc(Mat_rows*sizeof(double));
        if(Result==NULL)
        {
                printf("memory not available");
                exit(-1);
	}
                                                                    
	tick_count t1=tick_count::now();	
	parallel_for(blocked_range<int>(0,Mat_rows),Mul(Matrix,Vector,Mat_rows,Mat_cols,Vect_size));
	tick_count t2=tick_count::now();
	double time_taken =(t2-t1).seconds();
	printf("resultant veotor is:\n");
/*	for(i=0;i<Mat_rows;i++)
	{
		printf("%lf\n",Result[i]);
	}*/
	printf("time taken is :%f\n",time_taken);
	printf("no of operations: %d\n",(2*Mat_rows*Vect_size));
	printf("performance is : %f\n",((2*Mat_rows*Vect_size)/(time_taken*us)));
	free(Matrix);
	free(Vector);
	free(Result);
}
