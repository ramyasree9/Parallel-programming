/******************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010


    Example 2.5		: alltoall.c

    Objective           : A MPI program to gather values from each 
                          process and store the output values in the 
                          global integer array A of dimension n on p 
                          process of cluster. Use MPI_AllgatherCommunication
                          library call in the program.

   Input                : None
  
   OutPut               : All gather data 

   Modified             : April 2010

   Created              : May 2008
                           National PARAM Supercomputing Facility

*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"

int main(int argc,char *argv[])
{
 int root=0,index=0,N=3,i=0;
 int *send_buff,*recv_buff;
 int Myrank,Numprocs,send_count,recv_count; 
 MPI_Status status;
 
 /*..........MPI Initialisation........*/
 
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&Myrank);
  MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);

  if( Numprocs != 3 )
  { 
    if( Myrank == 0 )
    {
      printf("You should have 3 processes to run this . Terminated\n");
     }
     MPI_Finalize();
     exit(0);
   }


/*........Allocate memory for send & receive buffer............*/
  send_count= N/Numprocs;
  recv_count=send_count;

  send_buff=(int *)malloc(N *sizeof(int));
  recv_buff=(int *)malloc(N *sizeof(int));
 
/*........Take input in send buffer for each process ...............................*/
  if(Myrank==0)
  {
   i=0;
   for(index=0;index<3;index++)
   {
     send_buff[index]=i++;
    }
  }
  if(Myrank==1)
  {
    i=3;
    for(index=0;index<3;index++)
    {
      send_buff[index]=i++;
    }
  }
                                         
 if(Myrank==2)
 {
  i=6;
  for(index=0;index<3;index++)
  {
    send_buff[index]=i++;
  }
 }
 
/*........Call MPI Alltoall ..........................*/                                        
  MPI_Alltoall(send_buff,send_count,MPI_INT,recv_buff,recv_count,MPI_INT,MPI_COMM_WORLD);


/*..........Printing Output..............................*/
     for(index = 0;index<N;index++)
     printf(" MyRank=%d  Receive Data = %d \n\n",Myrank,recv_buff[index]);
  
/*..........MPI finalizing................................*/
  MPI_Finalize(); 
} 
