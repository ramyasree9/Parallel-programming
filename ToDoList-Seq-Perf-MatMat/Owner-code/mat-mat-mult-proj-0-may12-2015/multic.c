#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include "multi.h"
 
double ** multi(double **Matrix,double **Vector,int Matrix_rows,int Matrix_cols,int Vector_rows,double *dif)
{	
	int 	 i,j;
 	double   **Result_matrix  = (double **)malloc(Vector_rows* sizeof(double *));
        struct   timeval Start_time,End_time;
        for(i=0;i<Vector_rows;i++)
	{
	 	Result_matrix[i]  = (double *)malloc(sizeof(double));
	}
        for(i=0;i<Vector_rows;i++)
	{
 		Result_matrix[i][0]=0;
	}

        gettimeofday(&Start_time,0);

	for(i=0;i<Matrix_rows;i++)
	{	
		for(j=0;j<Matrix_cols;j++)
			{
				Result_matrix[i][0]=Result_matrix[i][0]+(Matrix[i][j]*Vector[j][0]);
			}
	}

	gettimeofday(&End_time,0);

	*dif  =(double)((double)End_time.tv_sec+((double)End_time.tv_usec/1000000))-((double)Start_time.tv_sec+((double)Start_time.tv_usec)/1000000);

	for(i=0;i<Vector_rows;i++)
	{
		printf("%f\n",Result_matrix[i][0]);
	}
        printf("time taken %f\n",*dif);
	return Result_matrix;
}
