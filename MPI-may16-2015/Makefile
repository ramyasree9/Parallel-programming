run : Send-recv-mpi.o
	mpicc -o run Send-recv-mpi.o
Send-recv-mpi.o:Send-recv-mpi.c
	mpicc -c Send-recv-mpi.c
clean:
	rm run Send-recv-mpi.o
