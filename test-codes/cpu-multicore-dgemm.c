/*
	Objective : To carry matrix matrix multiplication by partition the Matrix B 
	            between CPU+GPU using CBLAS+CUBLAS - BLAS3 library functions	 
	Input	  : Size of the matrix row size, matrix column size 
	Output	  : Time Taken for computation , Gflop/s 
	Author 	  : Nisha Agarwal
		    Abhishek Chintala		

        updated by sonia bansal	
*/

#include <stdio.h>
#include <stdlib.h>
# include <sys/time.h>


/* CBLAS header file inclusion*/
	#include <mkl.h>
//	#include <cblas.h>


#define EPS 1.0e-12 /* threshhold aprrox epsilion value */ 


#define LINE_DOT "\n.....................................................................................................\n"
#define LINE "\n__________________________________________________________________________________________________________\n"


/* Main function */
int main(int argc, char** argv)
{
	int 		rowA, rowB, rowC, colA, colB, colC; /* holds matrices dimensions */
	int		M, K, N, i, Size,  lda, ldb, ldc; /* holds matrices dimension and leading dimension */
	double		alpha = 1.0, beta = 0.0; 
	double*		hMatA;	/* host matrix A */
	double*		hMatB;  /* host matrix B */
	double*		hMatC;  /* host matrix C */
	float 		*elapsedTime; /* holds total elapsed time */
	double  	Gflops;	/* holds FLOPS */
	double 		Tsec_cpu=0.0,Tsec_gpu=0.0; /* holds time taken for computation on CPU */
        struct 	timeval	tv_start, tv_end; /* variable to hold start / end time for CPU*/



	//printf("\n ***************** Code  : CPU +  DGEMM (BLAS-III  ) ***********************\n");

	if (argc != 4 ){
		printf("\n Invalid number of arguments : <./executable>  <rowA > <colA/rowsB> <colB> \n");
		exit(-1);
	}	
	

	 /* read matrices size from command line arguments */
	 M = atoi(argv[1]) ;
         K = atoi(argv[2]);
         N = atoi(argv[3]);

	if ( N % 2 !=0 ) {
	 	 printf("\n  Usage : <./executable> <rowA > <colA/rowsB> <colB> ");
               	 printf(" \n Column of Matix B [ argv[3] ] should be divisible by 2 .. exiting \n\n");
                exit(-1); 
	}
	
	rowA = M ; /* set rows of matrix A */
  	colA = rowB = K ; /* set column of matrix A and rows of matrix B */
        colB = N ; /* set column of matrix B*/
		
	rowC = M ; /* set rows of resultant matrix C */
	colC = N ; /* set columns of resultant matrix C */


        Size = N ; 

        lda = M ; ldb = K ; ldc = M; /* set the leading dimension of matrices */


 	// Memory Allocation of the Matrices on the Host using pageable  Memory 
 	 hMatA = (double*) malloc (rowA * colA * sizeof(double));
        if (hMatA == 0){
        printf("\n Memory allocation Failed for Matrix A");
        exit (0);
        }

        hMatB = (double*) malloc (rowB * colB * sizeof(double));
        if (hMatB == 0){
        printf("\n Memory allocation Failed for Matrix B");
        exit (0);
        }

        hMatC = (double*) malloc (rowC * colC * sizeof(double));
        if (hMatC == 0){
        printf("\n Memory allocation Failed for Resultant Matrix");
        exit (0);
        }


	/* Filling the Matrix with double precision random values*/
	for (i = 0; i < rowA * colA; i++){
		hMatA[i] = drand48();
	}
	for (i=0; i < rowB * colB; i++){
		hMatB[i] = drand48(); 
	}
	for (i=0; i < rowC * colC; i++){
		hMatC[i] = 0.0 ; 
	}

 
	
	gettimeofday(&tv_start,0);
	/***** Performs operation using CBLAS DGEMM*******/
	cblas_dgemm (CblasColMajor, CblasNoTrans, CblasNoTrans, M, Size , K, alpha, hMatA, lda , hMatB , ldb, beta, hMatC, ldc);
	gettimeofday(&tv_end,0);

	

	/* compute total time taken for computation on CPU */
	Tsec_cpu = ((double)tv_end.tv_sec + (((double) (tv_end.tv_usec) /1000000.0))) - ((double)tv_start.tv_sec + (((double) (tv_start.tv_usec) /1000000.0)))  ;
	

	/* Compute Gflops */
	 Gflops= ( 1.0e-3 * (1.0e-6 * ((2. * M *K * Size) /Tsec_cpu))) ;


        printf(LINE_DOT);
        printf("Matrix-Size \t Comp Time(CPU+GPU Sec) \t  CBLAS GFlops ");
        printf(LINE_DOT);
        printf("\n %d * %d  \t %.8lf  \t\t\t %.8lf", M, N,(Tsec_cpu )  , Gflops );
        printf(LINE_DOT);


        printf(LINE);
        printf("\n");

/*
	printf("\n Printing resultant Matrix \n");
	for (i=0; i < M * N; i++){
		printf("\t %f \n",hMatC[i]);
	}

*/

        /**********************************/


   
	 free(hMatA);
        free(hMatB);
        free(hMatC);



}
