
/*
***********************************************************************
*******************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

    Example 1.6		:  sum_associative_fanin_blocking_tree.c

   Objective           : To find sum of 'n' integers on 'p' processors using 
                         'Associative Fan-in' rule.
                         MPI Blocking communication library calls are used.

                         This example demonstrates the use of 
                         MPI_Init
                         MPI_Comm_rank
                         MPI_Comm_size
                         MPI_Recv
                         MPI_Send
                         MPI_Finalize

   Input               :  Automatic input generation
            	           The rank of each process is input on each process.

   Output              : Process with Rank 0 should print the sum of 'n' values 

   Modified            : April 2010
   Created             : May 2008
                         National PARAM Supercomputing Facility

   Necessary           : Number of Processes should be less than 
   Condition             or equal to 8


************************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define  LOG2(x)    log10((double)(x)) / log10((double) 2)
#define  IS_INT(x)  ((x) == (int)(x))?1:0

int main(int argc,char *argv[])
{
    int   MyRank, Numprocs;
    int   Root = 0;
    int   ilevel, value, ans;
    int	  Source, Source_tag;
    int	  Destination, Destination_tag;
    int	  Level, NextLevel;
    float NoofLevels;
    static int	sum = 0;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    /* Check for the no. of processors to be a power of 2 */

    NoofLevels = LOG2(Numprocs);
    if(!(IS_INT(NoofLevels))){
        if(MyRank == Root)
	  printf("\nNumber of processors should be power of 2\n");
        MPI_Finalize();
        exit(-1);
    }

    sum = MyRank; 
    Source_tag = 0;
    Destination_tag = 0;

    for(ilevel = 0 ; ilevel < NoofLevels ; ilevel++) {
	Level = (int)(pow((double)2, (double)ilevel));
	
	if((MyRank % Level) == 0){
	    NextLevel = (int)(pow((double)2, (double)(ilevel+1)));

	    if((MyRank % NextLevel) == 0){
	        Source = MyRank + Level;
	     	MPI_Recv(&value, 1, MPI_INT, Source, Source_tag, 
			  MPI_COMM_WORLD, &status);
	     	sum = sum + value;
	    }
	    else{
	        Destination = MyRank - Level;
	     	MPI_Send(&sum, 1, MPI_INT, Destination, Destination_tag, 
			  MPI_COMM_WORLD);
	    }
        }
    }
	     
    if(MyRank == Root) 
       printf(" My Rank %d Final SUM %d\n", MyRank, sum);

     MPI_Finalize();
}



