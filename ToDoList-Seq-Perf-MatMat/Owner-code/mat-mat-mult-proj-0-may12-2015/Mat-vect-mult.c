#include<stdio.h>
#include<assert.h>
#include "input.h"
#include "input-matrix.h"
#include "input-vector.h"
#include "init.h"
#include "multi.h"
main()
{
   int           Matrix_rows,Matrix_cols,Vector_rows;
   double        **Matrix,**Vector,**Result_matrix,Time_taken,Mflops;
                         input(&Matrix_rows,&Matrix_cols,&Vector_rows);
                        /* check if matrix and vector can be created for given input rows and columns*/
                           assert((Matrix_rows>=1) && (Matrix_cols>=1) &&( Vector_rows>=1));
                        /* check if mat-vect-mult is possible or not*/
                           assert(Matrix_cols==Vector_rows);
		           printf("%d%d%d",Matrix_rows,Matrix_cols,Vector_rows);
     Matrix        =       input_matrix(Matrix,Matrix_rows,Matrix_cols);
     Vector        =       input_vector(Vector,Vector_rows); 
                           init(Matrix,Vector,Matrix_rows,Matrix_cols,Vector_rows);
     Result_matrix =       multi(Matrix,Vector,Matrix_rows,Matrix_cols,Vector_rows,&Time_taken);
     Mflops        =       (1.0e-6*2*Matrix_rows*Vector_rows)/Time_taken;
     printf("performance in mflops is %f ",Mflops); 
   	
}
