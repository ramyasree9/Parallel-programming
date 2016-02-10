
/*
***************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

  Example 1.2		: hello_world_slave.c MPMD Programme	


   Objective           : MPI Program to print "Hello World"
                         This example demonstrates the use of 
                         MPI_Init
                         MPI_Comm_rank
                         MPI_Comm_size
                         MPI_Send
                         MPI_Recv
                         MPI_Finalize

   Input               : Message = "Hello World" 

   Output              : Message and Rank of the process. 

   Modified            : April 2010
   Created             : May 2008
                         National PARAM Supercomputing Facility


   Necessary Condition : Number of processes should be 
                         less than or equal to 8. 

***************************************************************
*/



/* ....Standard Includes.... */

#include <stdio.h>
#include "mpi.h"

#define BUFFER_SIZE 200

int main(argc,argv)
int argc;
char *argv[];
{
    int  MyRank,Numprocs, Destination, Source, iproc;
    int  Destination_tag, Source_tag; 
    int  Root = 0,len_name ;
    char proc_name[100],proc_name_root[100];
  /*  char Message[BUFFER_SIZE]; */
	 MPI_Status status;

    /*....MPI initialization.... */

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs); 
    if(MyRank != 0)
    {
       char Message[BUFFER_SIZE]; 
       sprintf(Message, "Hello World");
       Destination = Root;
       Destination_tag = 0;
       MPI_Get_processor_name(proc_name, &len_name);
       printf("\n MPMD : Process with Rank %d [Node : %s] Sending MESSAGE \"%s\" to Process with Rank %d \n\n",MyRank,proc_name,Message,Root);
       MPI_Send(Message, BUFFER_SIZE, MPI_CHAR, Destination, Destination_tag, 
		MPI_COMM_WORLD);
    }
    
/*  ....Finalizing the MPI....*/
    MPI_Finalize();
}



