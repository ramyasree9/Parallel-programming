
/*
***************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

  Example 1.1		: hello_world.c	SPMD Programme


   Objective           : MPI Program to print "Hello World"
                         This example demonstrates the use of 

                         MPI_Init
                         MPI_Comm_rank
                         MPI_Comm_size
                         MPI_Send
                         MPI_Recv
                         MPI_Finalize

   Input               : Send_Message = "Hello World" 

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
     MPI_Status status;

    /*....MPI initialization.... */

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs); 
    if(MyRank != 0)
    {
       char Send_Message[BUFFER_SIZE]; 
       sprintf(Send_Message, "Hello World");
       Destination = Root;
       Destination_tag = 0;
       MPI_Get_processor_name(proc_name, &len_name);
       printf("\n SPMD : Process with Rank %d [Node : %s] Sending MESSAGE \"%s\" to Process with Rank %d \n\n",MyRank,proc_name,Send_Message,Root);
       MPI_Send(Send_Message, BUFFER_SIZE, MPI_CHAR, Destination, Destination_tag, 
		MPI_COMM_WORLD);
    }
    else 
    {
       char Recv_Message[BUFFER_SIZE];  

       for(iproc = 1 ; iproc < Numprocs ; iproc++) {
	   Source = iproc;
	   Source_tag = 0;
           MPI_Get_processor_name(proc_name_root, &len_name);
           MPI_Recv(Recv_Message, BUFFER_SIZE, MPI_CHAR, Source, Source_tag, 
		    MPI_COMM_WORLD, &status);
	   printf("\n SPMD : Process with Rank %d [Node : %s] Received MESSAGE \"%s\"   from Process with Rank %d\n\n",Root,proc_name_root,Recv_Message,iproc);
       }
    }
    
/*  ....Finalizing the MPI....*/
    MPI_Finalize();
}



