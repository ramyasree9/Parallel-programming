			//	        OPECG 2009
		       //	   June 01 - 05, 2009


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int Numprocs,MyRank,Root=0,Arraysize=45,Totalelements = 0;
	int index,iprocs,Send_Count,disp_value,pos=0,send_buff[Arraysize];
	int Destination,Destination_tag,Source,Source_tag,Totalsend=0;
	int *Displacement,count=0;
	int *My_gatherv,*Total_gatherv,*recv_count,*Recv_Buffer;
	MPI_Status status;

/*.............MPI Initilization...................*/
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
	MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

	if(Numprocs != 4)
	{
		if(MyRank == Root)
			printf("\n Number of Processes must be four in number\n");
		MPI_Finalize();
		exit(-1);
	}
      
      for(index=0;index<Arraysize;index++)
     {
      send_buff[index]=index;
     } 
/*.......Input the Gather size for each process...........................*/
        recv_count = (int *)malloc(Numprocs *sizeof(int));
        for(iprocs=0;iprocs<Numprocs;iprocs++) 
        {
           recv_count[iprocs]=iprocs+5;
        }


        Displacement = (int *)malloc(Numprocs *sizeof(int));
        Displacement[0]=0;
        
        for(iprocs =1; iprocs<Numprocs; iprocs++)
        {
          disp_value = 0;
          for(index = 0; index<iprocs; index++)
          {
            disp_value = disp_value+recv_count[index];
            Displacement[iprocs] = disp_value;
          }
        }


	if(MyRank == Root)
	{
        	for(iprocs =1; iprocs<Numprocs; iprocs++)
        	{
            		Destination = iprocs;
            		Destination_tag = 0;
            		Send_Count =recv_count[iprocs];
            		MPI_Send(&Send_Count,1,MPI_INT,Destination,
                                Destination_tag,MPI_COMM_WORLD);
         	}
        }
         if(MyRank>0)
        {
            Source = Root;
            Source_tag = 0;
            MPI_Recv(&Send_Count,1,MPI_INT,Source,Source_tag,MPI_COMM_WORLD,&status);
             My_gatherv=(int *)malloc(Send_Count *sizeof(int));
        }


/*........Allocate the memory for total gather buffer..................*/
         if(MyRank==0)
         {
            Total_gatherv=(int *)malloc(Arraysize *sizeof(int));
	     My_gatherv=(int *)malloc(recv_count[MyRank] *sizeof(int));
           pos=0;  
            for(index=0;index<recv_count[MyRank];index++)
            {
               My_gatherv[index]=send_buff[pos++];
            }

          }
/*.........Take input buffer for each process............................*/

         if(MyRank==1)
          {
          pos=recv_count[MyRank-1]; 
 for(index=0;index<recv_count[MyRank];index++)
            {
               My_gatherv[index]=send_buff[pos++];

            }
           }

         if(MyRank==2)
         {
         pos=recv_count[MyRank-1]+recv_count[MyRank-2]; 
           for(index=0;index<recv_count[MyRank];index++)
            {
              My_gatherv[index]=send_buff[pos++];
            }

          }

        if(MyRank==3)
        {
          pos=recv_count[MyRank-1]+recv_count[MyRank-2]+recv_count[MyRank-3];
             for(index=0;index<recv_count[MyRank];index++)
             {
               My_gatherv[index]=send_buff[pos++];
            }

           }


	MPI_Gatherv(My_gatherv,Send_Count,MPI_INT,
			Total_gatherv,recv_count,Displacement,MPI_INT,Root,MPI_COMM_WORLD); 
	if(MyRank == 0)
	{
	for(index = 0; index < Numprocs; index++)
		Totalelements = Totalelements + recv_count[index];	
	for(index = 0; index<Totalelements; index++)
	{
		printf("\n My Rank is : %d Recv_Buffer[%d] = %d \n",MyRank,index,Total_gatherv[index]);
	}
	}
   MPI_Finalize();
}
